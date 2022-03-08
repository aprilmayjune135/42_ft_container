#pragma once
#include <ctime>

namespace utility {
	
class Timer {
	public:
		Timer();
		void	reset();
		double	elapsed() const;
	private:
		time_t	start;
};

} /* end of namespace utility */
