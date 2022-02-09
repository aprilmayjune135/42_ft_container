#include "Print.hpp"
#include <iostream>

#ifndef STANDARD
#define LOG_FILE "ft_log.txt"
#else
#define LOG_FILE "std_log.txt"
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
