#pragma once
#include <fstream>

#define PRINT	Print().get()

class Print {
	public:
		Print();
		~Print();
		std::ofstream&	get();

	private:
		Print(const Print& src);
		
		std::ofstream	log;
		
		
};
