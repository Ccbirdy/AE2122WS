#include "enhance.h"
#include <vector>

int to_gray(int red, int green, int blue){
    return int(0.2989 * red + 0.5870 * green + 0.1140 * blue);
}


std::vector<int>& generate_pad (std::vector<int>& gray_pic, std::vector<int>& image_pad, std::vector<int>& pad_part, 
                    int offset, int num_rows, int pixel_per_row, int pad_pixel_per_row) {
    int i, j;

//#pragma omp ordered 
    for( j = 0; j<num_rows; j++) {
        for(i =0; i< pixel_per_row; i++) {
            image_pad.push_back(gray_pic[i + j*pixel_per_row]);
        }
        image_pad.insert(image_pad.end(), pad_part.begin(), pad_part.end());
    }
//#pragma omp ordered 
    for(i = 0; i< offset*pad_pixel_per_row - offset; i++) {
        image_pad.push_back(0);
    }  

}