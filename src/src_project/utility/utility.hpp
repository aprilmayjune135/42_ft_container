#pragma once
#include "color.hpp"
#include <string>

namespace utility {

/* debug */
void	printColor(const std::string& color, const std::string message);
void	printMagenta(const std::string& message);
void	printRed(const std::string& message);
void	printGreen(const std::string& message);
void	printBlue(const std::string& message);
void	printYellow(const std::string& message);
void	printTitle(const std::string& title);

} /* end of namespace utility */
