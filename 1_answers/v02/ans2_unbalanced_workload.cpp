#include <iostream>
#include <omp.h>
#include <vector>
//g++ -fopenmp ans2_unbalanced_workload.cpp -o ubl
using namespace std;

struct image;

image *denoise_image(image *in, int scale) { // mock denoise
  image *out = nullptr;
  const int loop_until = 20000 * scale; // unbalanced workload
  for (volatile int i = 0; i < loop_until; ++i) {}
  return out;
}

int main() {
  int amount_images = 64;
  vector<image *> images(amount_images, nullptr); // mock images
  vector<image *> denoised_images(amount_images); // mock output
  double start = omp_get_wtime();
  
  // #pragma omp parallel for is an "OpenMP shortcut"
//#pragma omp parallel for num_threads(4) // denoise a bunch of images
#pragma omp parallel for schedule(static,8) 
// I choose static because in for loop each iteration need same workload
  for (int i = amount_images - 1; i > -1; --i) {
    denoised_images[i] = denoise_image(images[i], i * i);
  }
  
  cout << omp_get_wtime() - start << " seconds" << endl;
}
