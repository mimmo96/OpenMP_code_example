#include <iostream>
#include <omp.h>
#include <unistd.h>

using namespace std;

int fibonacci(int i) {
    int res;
    // std:: cout << "Computing fib(" << i << ") on thread " <<  omp_get_thread_num() << std::endl;

    if (i<2)
        res=1;
    else {
        int i1=0;

        #pragma omp task shared(i1)
        { // default is firstprivate ... doesn't work
            i1 = fibonacci(i-1);
        }

        int i2=0;

        #pragma omp task shared(i2)
        { 
            i2 = fibonacci(i-2);
        }
        
        // before giving the result, await computation of i1
        #pragma omp taskwait
            res = i1 + i2;
    }

    return res;
}

int main(int argc, char * argv[]) {

    if (argc != 3) {
        cout << "Usage is" << argv[0] << "n nw " << endl;
        return(0);
    }

    int n = atoi(argv[1]);
    int nw = atoi(argv[2]);

    #pragma omp parallel num_threads (nw)
    {

        #pragma omp single
        {
            cout << "Working with " << omp_get_num_threads() << " threads "<< endl;
            auto t0 = omp_get_wtime();
            auto fib = fibonacci(n);
            auto elapsed = omp_get_wtime() - t0;
            cout << "fibonacci(" << n << ")"<< fib << " computed in "
            << elapsed << " secs " << endl;
        }
    }

return(0);
}