#include "Print.hpp"
#include <iostream>

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
