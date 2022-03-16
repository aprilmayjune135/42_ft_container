#include "print_color.hpp"
#include <limits>
#include <iostream>

namespace utility {

void	ignoreLine() {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template <class T>
T	getInput(const std::string& prompt, bool (*f_validation)(const T&)) {
	while (true) {
		printMagentaOneLine(prompt);
		T input;
		std::cin >> input;

		if (std::cin.fail() || !f_validation(input)) {
			std::cin.clear();
			ignoreLine();
			printRed("Invalid input. Please try again.");
		}
		else {
			ignoreLine();
			return input;
		}
	}
}

} /* end of namespace utility */
