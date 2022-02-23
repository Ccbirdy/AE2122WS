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
    int i, j;
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
    int filter_mask_size = 55, pad_num_rows, pad_pixel_per_row;     
    int offset = filter_mask_size/2;

    








    
    cout<< "start writing" << endl;
    // // Explicitly zero-pad the gray image
    // pad_num_rows = num_rows + 2*offset;
    // pad_pixel_per_row = pixel_per_row + 2*offset;    
    // vector<int> pad_pic(pad_pixel_per_row*offset*2, 0);

    //Write vector to output file
    for(i = 0; i < pixel_per_row*num_rows; i++ ){
        // //Write converted values to output file
        fout << gray_pic[i] << " "<< gray_pic[i] << " "<< gray_pic[i] << endl;            
    }   
 
    cout << omp_get_wtime() - start << " seconds" << endl;
    //Close files
    fin.close();
    fout.close();
    return 0;
}