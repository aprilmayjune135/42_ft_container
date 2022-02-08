#pragma once
#include <string>

namespace utility {

/* print_color */
void	printColor(const std::string& color, const std::string message);
void	printMagenta(const std::string& message);
void	printRed(const std::string& message);
void	printGreen(const std::string& message);
void	printBlue(const std::string& message);
void	printYellow(const std::string& message);
void	printColorOneLine(const std::string& color, const std::string message);
void	printMagentaOneLine(const std::string& message);
void	printRedOneLine(const std::string& message);
void	printGreenOneLine(const std::string& message);
void	printBlueOneLine(const std::string& message);
void	printYellowOneLine(const std::string& message);
void	printTitle(const std::string& title);

} /* end of namespace utility */
