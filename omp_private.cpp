#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

using namespace std::literals::chrono_literals;
using namespace std;

int main(int argc, char * argv[]) {
    auto nw = 1;
    if (argc != 1) nw = atoi (argv[1]);

    auto x = 123;
    
    #pragma omp parallel num_threads(nw) private(x)
    {
        
        auto dx =  rand()%8;
    
        #pragma omp critical
            cout << "Thread " << omp_get_thread_num() << " x = " << x << " adding " << dx << endl;
            this_thread::sleep_for(chrono::seconds(dx));
            x += dx;

        #pragma omp critical
            cout << "Thread ends " << omp_get_thread_num();
    }    // end parallel

    cout << "(main) Thread ends " << omp_get_thread_num() << " x= " << x << endl;

    return(0);
}