#include "Print.hpp"
#include <iostream>

#if defined(STANDARD)
#define LOG_FILE "std.log"
#elif defined(FSANITIZE)
#define LOG_FILE "fsanitize.log"
#else
#define LOG_FILE "ft.log"
#endif

Print::Print() {
	log.open(LOG_FILE, std::ios_base::app);
	if (!log.is_open()) {
		std::cerr << "Cannot open log.txt\n";
		return ;
	}
}

Print::~Print() {
	log.close();
}

std::ofstream&	Print::get() {
	return log;
}
