#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <omp.h>
#include "enhance.h"

// 1: convert in.jpg -compress none out.ppm  // convert jpg into ppm so c++ can easier read and process
// compile: g++ -Ofast -std=c++11 -march=native -fopenmp main.cpp -o proj
//  mkdir -p build
//  cmake -DCMAKE_CXX_COMPOLER=g++ -DCMAKE_BUILD_TYPR=Release ..
//  cmake --build .


using namespace std;
// int to_gray(int red, int green, int blue){
//     return int(0.2989 * red + 0.5870 * green + 0.1140 * blue);
// }

int main() {
    //File input and output streams
    std::ifstream fin("out.ppm");
    std::ofstream fout("output.ppm");
    //Check if input file was successfully opened
    if (!fin) {
        cout << "Error - Nonexistent Image (.ppm) File" << endl;
        system("pause");
        return -1;  // Error exit
    }
    //const double start = omp_get_wtime();
    //Declare necessary variables
    string magic_number;
    int pixel_per_row, num_rows, color_depth, red, green, blue;
    //Read in values for the following variables from input file
    fin >> magic_number >> pixel_per_row >> num_rows >> color_depth;
    //Write the following variables to the output file
    fout << magic_number << endl;  
    fout << pixel_per_row << " " << num_rows << endl << color_depth << endl;   
    //Read in input file convert it in gray scale and save in vector
    int i, j, k1, k2, local_sum;
    vector<int> gray_pic(pixel_per_row*num_rows, 0);
//#pragma omp ordered 
    // convert rgb picture into gray scale
    for(i = 0; i < pixel_per_row*num_rows; i++ ){
        fin >> red >> green >> blue;
        //Covert each pixel to grayscale               
        gray_pic[i] = to_gray(red, green, blue); 
    }   
   
    //cout << "finish generate gray_sacle_image: " << omp_get_wtime() - start << " seconds" << endl;
    cout<< " Start pictrure enhancement" << endl;
    //Declare necessary variables for the adaptive_threshold_mean_C 
    int filter_mask_size = 55, C = 10, pad_num_rows, pad_pixel_per_row;     
    int offset = filter_mask_size/2;
    pad_num_rows = num_rows + 2 * offset;
    pad_pixel_per_row = pixel_per_row + 2 * offset;
    // build filter mask
    float filter_mask = 1.0 /(filter_mask_size*filter_mask_size);
    const double start = omp_get_wtime();
    // Explicitly zero-pad the original image
    vector<int> pad_part(2*offset, 0);
    vector<int> image_pad(offset*pad_pixel_per_row + offset , 0);
//#pragma omp parallel //!!Speicherzugriffsfehler
#pragma omp ordered 
    for( j = 0; j<num_rows; j++) {
        for(i =0; i< pixel_per_row; i++) {
            image_pad.push_back(gray_pic[i + j*pixel_per_row]);
        }
        image_pad.insert(image_pad.end(), pad_part.begin(), pad_part.end());
    }
#pragma omp ordered 
    for(i = 0; i< offset*pad_pixel_per_row - offset; i++) {
        image_pad.push_back(0);
    }   
    
    cout << "finish generate padding image: " << omp_get_wtime() - start << " seconds" << endl;
    // Convolve
#pragma omp parallel for collapse(2) private(local_sum) 

    for(j=0; j< num_rows; j++){        
        for(i = 0; i< pixel_per_row; i++){

            //local_sum = 0;
//#pragma omp parallel for reduction(+ : local_sum)// !!make it slow!

            for ( k1 = 0; k1< filter_mask_size; k1++){
                for ( k2 = 0; k2< filter_mask_size; k2++){                    
                    local_sum += image_pad[i + j*pad_pixel_per_row + k2 +k1*pad_pixel_per_row];
                }
            }
//#pragma omp taskwait //!!make it slow!
            local_sum = local_sum * filter_mask -C;                 
        
            if (gray_pic[i+j*pixel_per_row] > local_sum){
            gray_pic[i+j*pixel_per_row] = color_depth;            
            }
            else{
                gray_pic[i+j*pixel_per_row] = 0;
            }
        }        
    }    

    
    cout << "finish calculate: " << omp_get_wtime() - start << " seconds" << endl;
    cout<< "start writing" << endl;

    //Write vector to output file
    for(const auto &e : gray_pic) fout << e << " "<< e << " "<< e << " ";

    cout << "finish writing: " << omp_get_wtime() - start << " seconds" << endl;

    //Close files
    fin.close();
    fout.close();
    return 0;
}