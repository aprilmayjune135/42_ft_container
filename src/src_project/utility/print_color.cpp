#include "print_color.hpp"
#include "color.hpp"
#include <iostream>

namespace utility {

void	printColor(const std::string& color, const std::string message) {
	std::cout << color << message << RESET_COLOR << '\n';
}

void	printMagenta(const std::string& message) {
	printColor(MAGENTA_BOLD, message);
}

void	printRed(const std::string& message) {
	printColor(RED_BOLD, message);
}

void	printGreen(const std::string& message) {
	printColor(GREEN_BOLD, message);
}

void	printBlue(const std::string& message) {
	printColor(BLUE_BOLD, message);
}

void	printYellow(const std::string& message) {
	printColor(YELLOW_BOLD, message);
}

void	printColorOneLine(const std::string& color, const std::string message) {
	std::cout << color << message << RESET_COLOR;
}

void	printMagentaOneLine(const std::string& message) {
	printColorOneLine(MAGENTA_BOLD, message);
}

void	printRedOneLine(const std::string& message) {
	printColorOneLine(RED_BOLD, message);
}

void	printGreenOneLine(const std::string& message) {
	printColorOneLine(GREEN_BOLD, message);
}

void	printBlueOneLine(const std::string& message) {
	printColorOneLine(BLUE_BOLD, message);
}

void	printYellowOneLine(const std::string& message) {
	printColorOneLine(YELLOW_BOLD, message);
}


void	printTitle(const std::string& title) {
	std::cout << MAGENTA_BOLD << "**********    " << title << "    **********"
		<< RESET_COLOR << '\n';
}

} /* end of namespace utility */
