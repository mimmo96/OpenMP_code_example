#include <iostream>
#include <thread>
#include <chrono>
#include <omp.h>

using namespace std::literals::chrono_literals;
using namespace std;

void inc(int& i) {
    auto temp = i;
    temp++;
    this_thread::sleep_for (10ms);
    i = temp;
    return;
}

int main(int argc, char* argv[]) {
    int i = 0;
    auto nw = 1;
    
    if (argc != 1) nw = atoi (argv[1]);

    #pragma omp parallel num_threads(nw)
    {
        #pragma omp atomic
            i += 1;
    }
    cout << "Eventually i = " << i << endl;

return(0);
}