#pragma once
#include <string>

#define RESET_COLOR		"\033[0m"
#define BLACK   		"\033[30m"
#define RED     		"\033[31m"
#define GREEN   		"\033[32m"
#define YELLOW  		"\033[33m"
#define BLUE    		"\033[34m"      
#define MAGENTA 		"\033[35m"
#define CYAN    		"\033[36m"
#define WHITE   		"\033[37m"

#define BLACK_BOLD   	"\033[1;30m"
#define RED_BOLD     	"\033[1;31m"
#define GREEN_BOLD   	"\033[1;32m"
#define YELLOW_BOLD  	"\033[1;33m"
#define BLUE_BOLD    	"\033[1;34m"
#define MAGENTA_BOLD 	"\033[1;35m"
#define CYAN_BOLD    	"\033[1;36m"
#define WHITE_BOLD   	"\033[1;37m"

//0 - Normal Style
//1 - Bold
//2 - Dim
//3 - Italic
//4 - Underlined
//5 - Blinking
//7 - Reverse
//8 - Invisible

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
