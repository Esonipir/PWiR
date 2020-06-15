#include <iostream>
#include <omp.h>
using namespace std;
int main()
{
    double pi = 0., sum = 0., x;
    const int N = 300000000;
    const double w = 1.0 / N;
    omp_lock_t writelock;
    omp_init_lock(&writelock);
#pragma omp parallel private(x), firstprivate(sum), shared(pi) num_threads(40)
    {
#pragma omp for
        for (int i = 0; i < N; ++i)
        {
            x = w * (i - 0.5);
            sum = sum + 4.0 / (1.0 + x * x);
        }
        omp_set_lock(&writelock);
        pi = pi + w * sum;
        omp_unset_lock(&writelock);
    }
    omp_destroy_lock(&writelock);
    cout << "Wynik PI = " << pi << endl;
}
