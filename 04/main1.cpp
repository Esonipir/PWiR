#include <omp.h>
#include <iostream>
using namespace std;

void w(long n)
{
    long sum = 0;
    cout << "i = " << (n / 10000000l)
         << " thread id = " << omp_get_thread_num() << endl;
    for (auto i = 0l; i < 20 * n; ++i)
        sum += i;
}

int main()
{
    const long max = 16, factor = 10000000l;
    const long chunk = 4;
#pragma omp parallel for schedule(static, chunk) num_threads(4)
    for (int i = 0; i < max; ++i)
        w(i * factor);
}
