#include <iostream>
#include <forward_list>
#include <vector>
#include <numeric>
#include <thread>
#include <omp.h>
using namespace std;

void processwork(size_t& n)
{
    #pragma omp critical
    std::cout << "Watek " << omp_get_thread_num() << " obliczajacy element " << n << std::endl;
    // Symulujemy jakas prace i zatrzymujemy watek
    std::this_thread::sleep_for(std::chrono::milliseconds(n*100));
    ++n;
}

int main ()
{
    forward_list<size_t> flist(30);
    iota(flist.begin(), flist.end(),1);
    
    double start = omp_get_wtime();
    #pragma omp parallel num_threads(1)  // tworzymy obszar rownolegly
    #pragma omp single    // tylko jeden watek utworzy zadania / tasks
    {
            for (auto& element : flist)
            {
                    #pragma omp task firstprivate (element)
                    processwork(element);
            }
            // czekamy az wszystkie taski sie skoncza
            #pragma omp taskwait
    }
    double stop = omp_get_wtime();
    cout << std::accumulate(flist.begin(),flist.end(),0) << endl;
    cout << "TIME: " << stop-start << endl;
}