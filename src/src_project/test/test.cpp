#include "test.hpp"
#include "../utility/get_input.hpp"

static void	displayContainer() {
	utility::printBlue("Available container type:");
	utility::printBlue("1. Vector");
	utility::printBlue("2. Map");
	utility::printBlue("3. Stack");
}

bool	checkScope(int n) {
	return (n >= 1 && n <= 3);
}

void	TestCase::init() {
	displayContainer();
	int n = utility::getInput<std::string>("Choose container (index): ", checkScope);
	container = static_cast<ContainerType>(n);
	
}
