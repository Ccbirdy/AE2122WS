#ifndef ENHANCE_H_
#define ENHANCE_H_

#include <vector>


int to_gray(int red, int green, int blue);

std::vector<int>& generate_pad (std::vector<int>& gray_pic, std::vector<int>& image_pad, std::vector<int>& pad_part, 
                    int offset, int num_rows, int pixel_per_row, int pad_pixel_per_row) ;



#endif /* end of include guard: ENHANCE_H_ */