#ifndef LOCK_
#define LOCK_
#include <sys/time.h>
#include <cstddef>
#include <omp.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;



class Timer{
public:
	Timer(){}

	void tic(){
	gettimeofday(&start,NULL);
}

	time_t toc(){
	gettimeofday(&end,NULL);
	time_t bibedibu=((end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);
    return bibedibu;
}

private:
	timeval start,end;

};

#endif // LOCK_
