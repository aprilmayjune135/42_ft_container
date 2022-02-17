#include "log_formatting.hpp"
#include "Print.hpp"

void	logTitleContainer(const std::string& container) {
	std::string	line(container.size() + 48, '*');
	PRINT << '\n';
	PRINT << line << '\n';
	PRINT << "**                      " << container << "                      **" << '\n';
	PRINT << line << '\n';
}

void	logTitleCategory(const std::string& container, const std::string& category) {
	PRINT << '\n';
	PRINT << "********** " << container << "_" << category << " **********" << '\n';
}

void	logTitleSection(const std::string& section) {
	PRINT << '\n';
	PRINT << "---------- " << section << " ----------" << '\n';
}

void	logTitleSubSection(const std::string& sub_section) {
	PRINT << '\n';
	PRINT << ">> " << sub_section << '\n';
}
