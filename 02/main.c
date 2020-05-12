#include <time.h> // zawiera clock_t and CLOCKS_PER_SEC
#include <stdio.h> // zawiera printf
#include <unistd.h> // zawiera sleep(int)

int main() {
    clock_t start, end;
    start = clock();
    sleep(1);
    end = clock();
    double duration_sec = (double)(end-start)/CLOCKS_PER_SEC;
    
    printf("Czas trwania = %f\n",duration_sec);
    printf("CLOCKS_PER_SEC = %d\n",CLOCKS_PER_SEC);
    return 0;
}