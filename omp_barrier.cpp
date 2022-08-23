#include <iostream>
#include <chrono>
#include <omp.h>
#include <thread>
#include <vector>

using namespace std::literals::chrono_literals;
using namespace std;

int main(int argc, char * argv[]) {

    int nw = (argc != 1 ? atoi (argv[1]) : 1);
    int seed=123;
    int x = 1;

    vector<int> r(nw);
    srand(seed);
    
    for (int i=0; i<nw; i++)
        r[i] = rand() % 8;

    #pragma omp parallel num_threads(nw)
    {
        auto id = omp_get_thread_num();

        #pragma omp critical
        {
            cout << "Ciao from id " << id << endl
                << "Working for " << r[id] << " secs" << endl;
        }

        auto dura = r[id]*1s;
        this_thread::sleep_for(dura);

        #pragma omp critical
            cout <<"Thread " << id << " waiting on barrier" << endl;

        #pragma omp barrier

        #pragma omp critical
            cout <<"Thread " << id << " passed on barrier!" << endl;

            dura = r[nw-id]*1s;
            this_thread::sleep_for(dura);

            cout << "Bye from " << id << endl;

    }

    return 0;
}
