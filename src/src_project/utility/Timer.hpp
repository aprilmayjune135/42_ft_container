#pragma once
#include <ctime>
#include <sys/time.h>

namespace utility {
	
class Timer {
	public:
		Timer();
		void	reset();
		double	elapsed_s() const;
		double	elapsed_ms() const;
	private:
		time_t	start_s;
		struct	timeval	start_ms;
};

} /* end of namespace utility */
