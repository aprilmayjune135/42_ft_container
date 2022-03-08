#include "Timer.hpp"

namespace utility {

Timer::Timer() {
	time(&start);
}

void	Timer::reset() {
	time(&start);
}

/* return in second */
double	Timer::elapsed() const {
	time_t	end;
	time(&end);
	return difftime(end, start);
}

} /* end of namespace utility */
