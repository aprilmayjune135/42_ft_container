#include "Timer.hpp"

Timer::Timer() {
	time(&start);
}

double	Timer::elapsed() const {
	time_t	now;
	time(&now);
	return difftime(now, start) * 1000;
}

void	Timer::reset() {
	time(&start);
}
