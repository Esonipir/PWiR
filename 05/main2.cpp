#include <iostream>
#include <omp.h>
using namespace std;
int main()
{
    int i;
    double x, pi, sum = 0.;
    const int N = 300000000;
    const double w = 1.0 / N;
#pragma omp parallel for private(x) reduction(+:sum)
    for (i = 0; i < N; ++i)
    {
        x = w * (i + 0.5);
        sum = sum + 4.0 / (1.0 + x * x);
    }

    pi = w * sum;
    cout << "Wynik PI = " << pi << endl;
}
