#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>
#include <unistd.h>

using namespace std::chrono_literals;
using namespace std;

int main(int argc, char * argv[]) {
    auto nw = 1;
    if (argc != 1) nw = atoi (argv[1]);

    auto x = 123;
    srand(getpid());
    
    #pragma omp parallel num_threads(nw)
    {
        #pragma omp sections lastprivate(conditional:x)
        {
            #pragma omp section
            {
                auto dx =  rand()%8;
    
                #pragma omp critical
                    cout << "Thread " << omp_get_thread_num() << " x = " << x << " adding " << dx << endl;
                    std::this_thread::sleep_for(chrono::seconds(dx));
                    x += dx;
                #pragma omp critical
                    cout << "Thread ends " << omp_get_thread_num() << " x = " << x << endl;
            }
            #pragma omp section
            {
                auto dx =  rand()%8;
    
                #pragma omp critical
                    cout << "Thread " << omp_get_thread_num() << " x = " << x << " adding " << dx << endl;
                    this_thread::sleep_for(chrono::seconds(dx));
                    x += dx;
                #pragma omp critical
                    cout << "Thread ends " << omp_get_thread_num() << " x = " << x << endl;
            } 
         }    // end sections
    }  // end parallel

    cout << "(main) Thread ends " << omp_get_thread_num() << " x= " << x << endl;

    return(0);
}