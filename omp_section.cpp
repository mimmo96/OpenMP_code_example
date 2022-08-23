#include <iostream>
#include <omp.h>
#include <thread>
#include <chrono>

using namespace std::literals::chrono_literals;
using namespace std;

int main(int argc, char * argv[]) {
    int nw = 1;
    if (argc != 1) nw = atoi(argv[1]);
    srand(getpt());

    #pragma omp parallel num_threads(nw)
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                int times = rand() % 32;
                    for (int i=0; i<times; i++) {
                        this_thread::sleep_for(chrono::milliseconds(101));
                        cout << "1";
                    }

                cout << "\n This is first section, thread " << omp_get_num_threads() << " of"
                    << omp_get_thread_num() << endl;
            }

            #pragma omp section
            {
                int times = rand() % 32;
                for (int i=0; i<times; i++) {
                    this_thread::sleep_for(chrono::milliseconds(101));
                    cout << "2";
                }

                 cout << "\nThis is first section, thread "<< omp_get_thread_num() << " of"
                << omp_get_num_threads() << endl;
            }
        }  //end section
    }   // end parallel

return(0);

}