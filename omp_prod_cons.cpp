#include <iostream>
#include <atomic>
#include <chrono>
#include <thread>
#include <omp.h>

using namespace std::literals::chrono_literals;
using namespace std;

std::atomic<int> presenceBit;
std::atomic<int> consumedBit;

int buffer;

int main(int argc, char * argv[]) {
    
    presenceBit = 0;
    consumedBit = 0;
    buffer = 0;
    
    auto delay =25;
    auto nw =1;

    if(argc!=1) nw= atoi(argv[1]);
    
    const int n=4;

    #pragma omp parallel num_threads(nw)
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                    cout << "This is the producer section, it is thread "
                    << omp_get_thread_num() << " of "
                    << omp_get_num_threads() << endl;
                for (int i=0; i<n; i++) {
                    cout << "Waiting buffer free fo send ..." << endl;
                    while(consumedBit == 0) { 
                        std::this_thread::sleep_for(1ms); 
                    }

                    std::this_thread::sleep_for(chrono::milliseconds(delay));
                    buffer = i;
                    consumedBit = 0;
                    presenceBit = 1;
                    
                    cout << "Sent!" << endl;
                }
            }
    
            #pragma omp section
            {
                cout << "This is second section, thread "
                << omp_get_thread_num() << " of"
                << omp_get_num_threads() << endl;
                
                consumedBit = 1; // ask for first buffer
            
                for (int i=0; i<n; i++){
                    cout << "Waiting for buffer full to receive ..." << endl;
                    while(presenceBit == 0) { this_thread::sleep_for(1ms); }
                    cout << "Received "<< buffer << endl;
                    presenceBit=0;
                    consumedBit=1;
                }
            }
        } // end sections
    } // end parallel

    std:: cout << "Both sections terminated . . ." << endl;
    return(0);
}