#include <iostream>
#include <omp.h>
#include <unistd.h>
using namespace std;

int main() {
    // mozliwosci ustawienia liczby watkow:
    // 1) zmienna srodowiskowa: OMP_NUM_THREADS
    // 2) funckja biblioteczna: omp_set_num_threads( int )
    // 3) klauzula: num_threads( int )
    #pragma omp parallel num_threads(4)
    {
        int ID = omp_get_thread_num();
        cout << "Hello world! " << ID << endl;
    }
    usleep(1000000);
}