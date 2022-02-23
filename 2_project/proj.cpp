#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <omp.h>


//g++ -Ofast -std=c++11 -march=native -fopenmp proj.cpp -o proj

using namespace std;

int main() {
    //File input and output streams
    ifstream fin("out.ppm");
    ofstream fout("output.ppm");
    //Check if input file was successfully opened
    if (!fin) {
        cout << "Error - Nonexistent Image (.ppm) File" << endl;
        system("pause");
        return -1;  // Error exit
    }
    const double start = omp_get_wtime();
    //Declare necessary variables
    string magic_number;
    int pixel_per_row, num_rows, color_depth, red, green, blue;
    //Read in values for the following variables from input file
    fin >> magic_number >> pixel_per_row >> num_rows >> color_depth;
    //Write the following variables to the output file
    fout << magic_number << endl << pixel_per_row << " " << num_rows << endl << color_depth << endl;
    //Read in input file until file end putting values into appropriate variables
    int i, j, k1, k2;
    vector<int> gray_pic(pixel_per_row*num_rows, 0);
    // convert rgb picture into gray scale
    for(i = 0; i < pixel_per_row*num_rows; i++ ){
        fin >> red >> green >> blue;
        //Covert each pixel to grayscale
        red = int(0.2989 * red + 0.5870 * green + 0.1140 * blue);         
        gray_pic[i]=red;
    }    
           
    cout<< "start pictrure enhancement" << endl;
    //Declare necessary variables for the adaptive_threshold_mean_C 
    int filter_mask_size = 21, C = 0, pad_num_rows, pad_pixel_per_row;     
    int offset = filter_mask_size/2;
    // build filter mask
    float filter_mask = 1.0 /(filter_mask_size*filter_mask_size);
    vector<int> convolved_image(gray_pic.size(), 0);
    // Explicitly zero-pad the original image
    vector<int> pad_part(2*offset, 0);
    vector<int> image_pad(offset*pad_pixel_per_row + offset , 0);
    for( i = 0; i<num_rows; i++) {
        for(j =0; j< pixel_per_row; j++) {
            image_pad.push_back(gray_pic[j + i*pixel_per_row]);
        }
        image_pad.insert(image_pad.end(), pad_part.begin(), pad_part.end());
    }
    for(i = 0; i< offset*pad_pixel_per_row - offset; i++) {
        image_pad.push_back(0);
    }
    

    // Convolve
    for(j=0; j< num_rows; j++){
        int local_sum = 0;
        for(i = 0; i< pixel_per_row; i++){
            for ( k1 = 0; k1< offset; k1++){
                for ( k2 = 0; k2< offset; k2++){
                    local_sum += image_pad[i + j*pixel_per_row + k2 +k1*pixel_per_row];
                }
            }
            local_sum = local_sum * filter_mask;
            local_sum = local_sum - C;

            if (gray_pic[i+j*pixel_per_row] > local_sum){
            convolved_image[i+j*pixel_per_row] = color_depth;            
            }
            else{
                convolved_image[i+j*pixel_per_row] = 0;
            }
        }        
    }


    cout << omp_get_wtime() - start << " seconds" << endl;
    cout<< "start writing" << endl;

    //Write vector to output file
    for(i = 0; i < pixel_per_row*num_rows; i++ ){
        // //Write converted values to output file
        fout << convolved_image[i] << " "<< convolved_image[i] << " "<< convolved_image[i] << endl;            
    }   
 
    cout << omp_get_wtime() - start << " seconds" << endl;
    //Close files
    fin.close();
    fout.close();
    return 0;
}