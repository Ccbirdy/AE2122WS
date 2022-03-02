#include "enhance.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <omp.h>
using namespace std;

int to_gray(int red, int green, int blue){
    return int(0.2989 * red + 0.5870 * green + 0.1140 * blue);
}


std::vector<int>& generate_pad (std::vector<int>& gray_pic, std::vector<int>& image_pad, std::vector<int>& pad_part, 
                    int offset, int num_rows, int pixel_per_row, int pad_pixel_per_row) {
    int i, j;

// #pragma omp ordered 
    for( j = 0; j<num_rows; j++) {
        for(i =0; i< pixel_per_row; i++) {
            image_pad.push_back(gray_pic[i + j*pixel_per_row]);
        }
        image_pad.insert(image_pad.end(), pad_part.begin(), pad_part.end());
    }
// #pragma omp ordered 
    for(i = 0; i< offset*pad_pixel_per_row - offset; i++) {
        image_pad.push_back(0);
    }  

}


void write_output(std::vector<int>& gray_pic, string magic_number, int pixel_per_row, 
                int num_rows, int color_depth){
    std::ofstream fout("output.ppm");
    //Write the following variables to the output file
    fout << magic_number << endl;  
    fout << pixel_per_row << " " << num_rows << endl << color_depth << endl;   
    for(const auto &e : gray_pic) fout << e << " "<< e << " "<< e << " ";
    fout.close();
}

std::vector<int>& convolve_img(int i, int j, int filter_mask_size, int pad_pixel_per_row,
            float filter_mask, int pixel_per_row, int color_depth,
            std::vector<int>& gray_pic, std::vector<int>& image_pad, int C){
    int k1,k2, local_sum = 0;
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