#include <iostream>
#include <omp.h>
using namespace std;

double pi_r(double h, unsigned depth, unsigned maxdepth, unsigned long long begin, unsigned long long niters)
{
    if (depth < maxdepth)
    {
        double area1, area2;

// przelicz pierwsza polowe
#pragma omp task shared(area1)
        area1 = pi_r(h, depth + 1, maxdepth, begin, niters / 2 - 1);

// przelicz druga polowe
#pragma omp task shared(area2)
        area2 = pi_r(h, depth + 1, maxdepth, begin + niters / 2, niters / 2);

#pragma omp taskwait

        return area1 + area2;
    }
    else
    {
        unsigned long long i;
        double area = 0.0;

        for (i = begin; i <= begin + niters; i++)
        {
            double x = h * (i - 0.5);
            area += (4.0 / (1.0 + x * x));
        }

        return area;
    }
}

double pi(unsigned long long nit)
{
    double res;
    double h = 1.0 / (double)nit;

#pragma omp parallel shared(res) num_threads(4)
    {
#define MAX_PARALLEL_RECURSIVE_LEVEL 4

#pragma omp single
        res = pi_r(h, 0, MAX_PARALLEL_RECURSIVE_LEVEL, 1, nit);
    }
    return res * h;
}

int main()
{
    unsigned long long niters = 300000000;

    cout << "PI (" << niters << " iteracji) = " << pi(niters) << endl;
}