#include <omp.h>
#include <iostream>
using namespace std;

static long num_steps = 300000000;
double step;
int main(int argc, char *argv[])
{
    const unsigned numthreads = atoi(argv[1]);
    int i;
    double pi, sum = 0.0;
    step = 1.0 / num_steps;
#pragma omp parallel num_threads(numthreads)
    {
        double x;
#pragma omp for schedule(dynamic, 1) reduction(+:sum)
        for (i = 0; i < num_steps; ++i)
        {
            x = (i + 0.5) * step;
            sum = sum + 4.0 / (1.0 + x * x);
        }
    }
    pi = step * sum;
    cout << "PI = " << pi << endl;
}