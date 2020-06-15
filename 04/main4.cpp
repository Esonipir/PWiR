#include <omp.h>
#include <iostream>
using namespace std;

void w(long n)
{
    long sum = 0;
    cout << "i = " << (n / 10000000l)
         << " thread id = " << omp_get_thread_num() << endl;
    for (long i = 0; i < 20 * n; ++i)
        sum += i;
}

int main()
{
    const long max = 16, factor = 10000000l;
#pragma omp parallel for schedule(auto) num_threads(4)
//#pragma omp parallel for schedule(runtime) num_threads(4)
    for (int i = 0; i < max; ++i)
        w(i * factor);
}
