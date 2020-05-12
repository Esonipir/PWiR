#include <iostream>
#include <chrono>
#include <ratio>
#include <thread>
using namespace std::chrono;

void f() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
 
int main() {
    auto t1 = std::chrono::high_resolution_clock::now();
    f();
    auto t2 = std::chrono::high_resolution_clock::now();
    // zmiennoprzecinkowe duration: duration_cast zbędne
    std::chrono::duration<double, std::milli> fp_ms = t2 - t1;
    // duration typu całkowitego: duration_cast wymagane
    auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
 
    // konwersja typu mniej pojemnego na bardziej pojemny, duration_cast zbędne
    std::chrono::duration<long, std::micro> int_microsec = int_ms;
 
    std::cout << "f() trwalo " << fp_ms.count() << " ms, "
              << "lub " << int_ms.count() << " calych milisekund "
              << "(= " << int_microsec.count() << " calych mikrosekund)" << std::endl;
    std::cout << "Konwersja 2m - 1m = ";
    std::cout << std::chrono::duration_cast<std::chrono::seconds>( 2min - 1min ).count() << " s." << std::endl;
}