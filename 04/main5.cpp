#include <omp.h>
#include <iostream>
#include <random>
using namespace std;

void v(long n)
{
    random_device rd;
    uniform_int_distribution<int> dist(1, 20);
    long sum = 0;
    long los = dist(rd);
    cout << "i = " << los
         << " thread id = " << omp_get_thread_num() << endl;
    for (long i = 0; i < los * n; ++i)
        sum += i;
}

int main()
{
    const long max = 16, factor = 10000000l;
#pragma omp parallel for schedule(auto) num_threads(4)
    for (int i = 0; i < max; ++i)
        v(factor);
}
