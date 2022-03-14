#include "Timer.hpp"

namespace utility {

Timer::Timer() {
	time(&start_s);
	gettimeofday(&start_ms, NULL);
}

void	Timer::reset() {
	time(&start_s);
	gettimeofday(&start_ms, NULL);
}

/* return in seconds */
double	Timer::elapsed_s() const {
	time_t	end_s;
	time(&end_s);
	return difftime(end_s, start_s);
}

/* return in milli-seconds */
double	Timer::elapsed_ms() const {
	struct timeval	end_ms;
	gettimeofday(&end_ms, NULL);
	return ((end_ms.tv_sec * 1000000 + end_ms.tv_usec) -
		(start_ms.tv_sec * 1000000 + start_ms.tv_usec)) / 1000;
}

} /* end of namespace utility */
