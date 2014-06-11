#include "timer.h"

Timer::Timer()
{};

void Timer::tic()
{
	gettimeofday(&start,NULL);
}

time_t Timer::toc()
{
	gettimeofday(&end,NULL);
	time_t bibedibu=((end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);
    return bibedibu;
}
