#include <vector>
#include <iostream>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>

using namespace std;

void foo(std::vector<int> test, int random)
{
        test.erase(test.begin()+random);
        test.push_back(1);
}

int main(int argc, char **argv)
{    
    int N = atoi(argv[1]);


    MPI_Init(&argc, &argv);
    int size;
    int rank;
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if (rank == 0){
        cout << "N: " << N << endl;
//        cout << "nt: " << omp_get_num_threads() << endl;
    }

    long unsigned n=1000000;
    std::vector<int> test(n,0);

    bool output=true;


    int nt = 4/size;
    omp_set_num_threads(nt);

    #pragma omp parallel for collapse(3) shared(test)
    for (int k=0; k<N; ++k) {
        for (int j=0; j<N; ++j) {
            for (int i=0; i<N; ++i) {  
                int random= rand() % n;
                foo(test,random);
                if(output){
                        cout << "nt: " << omp_get_num_threads() << endl;
                        output=false;
                    }
            }
        }
    }   
    std::cout<<test.at(10);

    MPI_Finalize();
    return 0;
}
