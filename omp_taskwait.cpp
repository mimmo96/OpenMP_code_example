#include <iostream>
#include <omp.h>
#include <unistd.h>

using namespace std;

int main(int argc, char * argv[])
{
    
    #pragma omp parallel
    #pragma omp single
    {
        #pragma omp task
        {
            #pragma omp critical
                cout << "Task 1" << endl;
            
            #pragma omp task
            {
                cout << "Task2 starts";
                sleep(1);
            
                #pragma omp critical
                    cout << "Task2 ends" << endl;
            }
        }

        #pragma omp taskwait

        #pragma omp task
        {
            #pragma omp critical
                cout << "Task3" << endl;
        }
    }

    return 0;
}