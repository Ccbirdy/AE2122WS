#include <iostream>
#include <omp.h>
#include <random>

using namespace std;
// g++ -fopenmp pi_monte_carlo_parallel.cpp -o ppim

int main() {
  int seed = 123;
  default_random_engine re{seed};
  uniform_real_distribution<double> zero_to_one{0.0, 1.0};

  int n = 100000000; // amount of points to generate
  int counter = 0; // counter for points in the first quarter of a unit circle
  auto start_time = omp_get_wtime(); // omp_get_wtime() is an OpenMP library routine
  omp_set_num_threads(2);
#pragma omp parallel// parallel region starts here------
  {
    int num_threads = omp_get_num_threads();
    int thread_id = omp_get_thread_num();
    double counter_local = 0.0;
  // compute n points and test if they lie within the first quadrant of a unit circle
    for (int i = thread_id; i < n; i += num_threads) {
      auto x = zero_to_one(re); // generate random number between 0.0 and 1.0
      auto y = zero_to_one(re); // generate random number between 0.0 and 1.0
      if (x * x + y * y <= 1.0) { // if the point lies in the first quadrant of a unit circle
        ++counter_local;
      }
    }
#pragma omp atomic
    counter += counter_local;
  }// parallel region ends here -------- 


  auto run_time = omp_get_wtime() - start_time;
  auto pi = 4 * (double(counter) / n);

  cout << "pi: " << pi << endl;
  cout << "run_time: " << run_time << " s" << endl;
  cout << "n: " << n << endl; }
