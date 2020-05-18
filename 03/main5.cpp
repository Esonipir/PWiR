#include <iostream>
#include <iomanip>
#include <omp.h>
using namespace std;

const long num_steps = 300'000'000;
int main(int argc, char *argv[])
{
    cout << setprecision(15) << fixed;
    const unsigned num_threads = stoi(argv[1]);
    long double pi = 0.0;
    long double step = 1.0 / num_steps;
    omp_set_num_threads(num_threads);
#pragma omp parallel
    {
        long i, id, nthrds;
        long double x;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        for (i = id; i < num_steps; i += nthrds)
        {
            x = (i + 0.5) * step;
    #pragma omp critical
            pi += 4.0 / (1.0 + x * x);
        }
    }
    pi *= step;
    cout << "PI = " << pi << endl;
    cout << "PI = "
         << "3.14159265358979323846264338327950288419716939937510582097494" << endl;
}
