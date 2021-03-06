#include <iostream>
#include <iomanip>
#include <omp.h>
using namespace std;

const long num_steps = 300'000'000;
const unsigned PAD = 8;

int main(int argc, char *argv[])
{
    cout << setprecision(15) << fixed;
    const unsigned num_threads = stoi(argv[1]);
    int i, nthreads;
    long double pi, sum[num_threads][PAD];
    long double step = 1.0 / num_steps;
    omp_set_num_threads(num_threads);
#pragma omp parallel
    {
        int i, id, nthrds;
        long double x;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if (id == 0) nthreads = nthrds;
        for (i = id, sum[id][0] = 0.0; i < num_steps; i += nthrds)
        {
            x = (i + 0.5) * step;
            sum[id][0] += 4.0 / (1.0 + x * x);
        }
    }
    for (i = 0, pi = 0.0; i < nthreads; ++i) pi += step * sum[i][0];
    cout << "PI = " << pi << endl;
    cout << "PI = "
         << "3.14159265358979323846264338327950288419716939937510582097494" << endl;
}