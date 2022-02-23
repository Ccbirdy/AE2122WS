#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <omp.h>


//g++ -Ofast -std=c++11 -march=native -fopenmp proj.cpp -o proj

using namespace std;

// int adapt_thres_mean_C(image, int Max_value, int filter_mask_size) {
//     // build filter mask
//     filter_mask = np.ones((filter_mask_size,filter_mask_size)) / (filter_mask_size * filter_mask_size)

//     convolved_image = np.zeros_like(image)
//     offset_y = filter_mask_size // 2
//     offset_x = filter_mask_size // 2

//     // Explicitly zero-pad the original image
//     image_pad = np.zeros((image.shape[0] + 2 * offset_y, image.shape[1] + 2 * offset_x), dtype=image.dtype)
//     image_pad[offset_y:offset_y+image.shape[0], offset_x:offset_x+image.shape[1]] = image

//     // Convolve
//     for cy in range(convolved_image.shape[0]):
//         for cx in range(convolved_image.shape[1]):
//             // Extract image patch of the same size as the mask centered around the current pixel,
//             // multiply it element-wise with the mask, and accumulate the results.
//             patch = image_pad[cy:cy+filter_mask.shape[0], cx:cx+filter_mask.shape[1]]
//             T = np.sum(patch * filter_mask) -C
            
//             if image[cy, cx] > T :
//                 convolved_image[cy, cx] = Max_Value
//                 #convolved_image[cy, cx] = np.max(patch)
//             else:
//                 convolved_image[cy, cx] = 0

//     return convolved_image;   
// }




int main() {
    std::ifstream fin("out.ppm", std::ios::binary);
    const string image_name = "output.ppm";
    remove(image_name.c_str()); // remove file from disk
    std::ofstream fout(image_name, std::ios::binary);
    
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
    int i;
    #pragma omp parallel for schedule(dynamic) 
        
        for(i = 0; i < pixel_per_row*num_rows; i++ ){
            fin >> red >> green >> blue;
            red = green = blue = int(0.2989 * red + 0.5870 * green + 0.1140 * blue); //Covert each pixel to grayscale
            fout << red << " " << green << " " << blue << endl; //Write converted values to output file
        }
         
    
    cout << omp_get_wtime() - start << " seconds" << endl;

      


    //Close files
    fin.close();
    fout.close();
    return 0;
}

