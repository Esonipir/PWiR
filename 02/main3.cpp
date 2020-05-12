#include <iostream>
#include <thread>
#include <iomanip>
#include <omp.h>
using namespace std;

void f() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
 
 
int main() {
    double start = omp_get_wtime();
    f();
    double stop = omp_get_wtime();
 
    cout << setprecision(4) << "Start: " << start
         << " stop: " << stop << " start-stop: " 
         << stop-start << endl;
    cout << "Precision: " << omp_get_wtick() << endl;
}