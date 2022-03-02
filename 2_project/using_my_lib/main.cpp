#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <omp.h>
#include "enhance.h"

// convert in.jpg -compress none out.ppm  // convert jpg into ppm so c++ can easier read and process
// go to 2_project/using_my_lib
// paste out.ppm in this folder
// mkdir build
// cd build
// ------ make clean  // from the next time
// cmake ..
// make
// ,.proj


using namespace std;



int main() {
    //File input and output streams
    std::ifstream fin("out.ppm");
    
    //Check if input file was successfully opened
    if (!fin) {
        cout << "Error - Nonexistent Image (.ppm) File" << endl;
        system("pause");
        return -1;  // Error exit
    }
    
    //Declare necessary variables
    string magic_number;
    int pixel_per_row, num_rows, color_depth, red, green, blue;
    //Read in values for the following variables from input file
    fin >> magic_number >> pixel_per_row >> num_rows >> color_depth;
      
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
   
    cout << "finish generate gray_sacle_image " << endl;
    cout << " Start pictrure enhancement" << endl;
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
// generate padding vector <image_pad> for vector <gray_pic>
    generate_pad( gray_pic, image_pad, pad_part, 
                   offset, num_rows, pixel_per_row, pad_pixel_per_row); 
    
    cout << "finish generate padding image: " << omp_get_wtime() - start << " seconds" << endl;
    // Convolve
#pragma omp parallel for collapse(2) private(local_sum) 
    for(j=0; j< num_rows; j++){        
        for(i = 0; i< pixel_per_row; i++){
            //local_sum = 0;
//#pragma omp parallel for reduction(+ : local_sum)// !!make it slow!
            convolve_img(i, j, filter_mask_size, pad_pixel_per_row, filter_mask,
                        pixel_per_row, color_depth, gray_pic, image_pad, C);
        }        
    }    
    
    cout << "finish calculate: " << omp_get_wtime() - start << " seconds" << endl;
    cout<< "start writing" << endl;

    //Write vector to output file
    write_output(gray_pic, magic_number, pixel_per_row, num_rows, color_depth);

    cout << "finish writing: " << omp_get_wtime() - start << " seconds" << endl;

    //Close files
    fin.close();
    return 0;
}