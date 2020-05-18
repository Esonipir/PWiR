#include <iostream>
#include <iomanip>
#include <omp.h>
using namespace std;

const long num_steps = 300'000'000;

int main()
{
    cout << std::setprecision(std::numeric_limits<long double>::digits10 + 1) << std::fixed;
    int i;
    long double x, pi, sum = 0.0;
    long double step = 1.0 / num_steps;
    for (i = 0; i < num_steps; ++i)
    {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }
    pi = step * sum;
    cout << "PI = " << pi << endl;
    cout << "PI = "
         << "3.14159265358979323846264338327950288419716939937510582097494" << endl;
}