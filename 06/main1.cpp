#include <iostream>
#include <forward_list>
#include <vector>
#include <numeric>
#include <thread>
#include <omp.h>
using namespace std;

static void processwork(size_t& n)
{
    #pragma omp critical
    std::cout << "Watek " << omp_get_thread_num() << " obliczajacy element " << n << std::endl;
    // Symulujemy jakas prace i zatrzymujemy watek
    std::this_thread::sleep_for(std::chrono::milliseconds(n*100));
    ++n;
}



int main()
{
    forward_list<size_t> flist(30);
    iota(flist.begin(), flist.end(),1);
    vector<size_t> vlist;
    copy(begin(flist),end(flist),back_inserter(vlist));
    size_t j = (size_t)vlist.size();
    double start = omp_get_wtime();
    #pragma omp parallel for schedule (static,1) num_threads(4)
    for (size_t i=0; i<j; ++i) {
        processwork(vlist[i]);
    }
    double stop = omp_get_wtime();
    cout << std::accumulate(vlist.begin(),vlist.end(),0) << endl;
    cout << "TIME: " << stop-start << endl;
}
