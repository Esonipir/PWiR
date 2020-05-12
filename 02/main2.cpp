#include <iostream>
#include <chrono>
#include <thread>

auto timeFuncInvocation = 
    [](auto&& func, auto&&... params) {
        // pobierz czas przed wywolaniem funkcji
        const auto& start = std::chrono::high_resolution_clock::now();
        // wywolanie funkcji za pomoca perfect forwarding
        std::forward<decltype(func)>(func)(std::forward<decltype(params)>(params)...);
        // pobierz czas po wywolaniu funkcji
        const auto& stop = std::chrono::high_resolution_clock::now();
        return stop - start;
     };


void f() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
 
 
int main() {
    auto t1 = std::chrono::high_resolution_clock::now();
    f();
    auto t2 = std::chrono::high_resolution_clock::now();
 
    std::cout << "Domyslna jednostka now() - liczba interwalow: " << (t2-t1).count() << std::endl;
    std::cout << "Licznik duration::period::num = " << std::chrono::high_resolution_clock::duration::period::num << std::endl;
    std::cout << "Mianownik duration::period::den = " << std::chrono::high_resolution_clock::duration::period::den << std::endl;

    std::cout << "Wynik timeFuncInvocation = ";
    std::cout << timeFuncInvocation(f).count() << std::endl;
}