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
	Timer();

	void tic();

	time_t toc();

private:
	timeval start,end;

};

#endif // LOCK_
