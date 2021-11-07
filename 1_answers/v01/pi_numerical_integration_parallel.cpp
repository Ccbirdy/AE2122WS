#include <iomanip>
#include <iostream>
#include <omp.h>
// g++ -fopenmp pi_numerical_integration_parallel.cpp -o piparallel
// OMP_NUM_THREADS=4 ./pi
using namespace std;

int main() {
    
    int num_steps = 100000000; // amount of rectangles
    double width = 1.0 / double(num_steps); // width of a rectangle

    for (int th = 4; th < 129; th++){
        double sum = 0.0; // for summing up all heights of rectangles

        double start_time = omp_get_wtime(); // wall clock time in seconds
        omp_set_num_threads(th);
    
    #pragma omp parallel// parallel region starts here------
        {
            int num_threads = omp_get_num_threads();
            int thread_id = omp_get_thread_num();
            double sum_local = 0.0;

            for (int i = thread_id; i < num_steps; i += num_threads) {
                double x = (i + 0.5) * width; // midpoint
                sum_local = sum_local + (1.0 / (1.0 + x * x)); // add new height of a rectangle
            }
    #pragma omp atomic
            sum+= sum_local;
        }// parallel region ends here --------    

        double pi = sum * 4 * width; // compute pi
        double run_time = omp_get_wtime() - start_time;

        cout << th <<"," << num_steps << "," << setprecision(17)
            << pi << "," << setprecision(6) << run_time << "\n";
    }  
}
