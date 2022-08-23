#include <iostream>
#include <omp.h>

using namespace std;

int main(int argc, char * argv[]) {
    
    int nw = 1;
    
    if(argc!=1)
        nw = atoi(argv[1]) ;
    
    #pragma omp parallel num_threads(nw)
    {
        auto id = omp_get_thread_num();
        cout<< "Ciao from id "<< id << endl;
    }

    return 0;
}