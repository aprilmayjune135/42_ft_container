#include "print_tree.hpp"

namespace utility {

void	showTrunk(Trunk* p) {
	if (p) {
		showTrunk(p->prev);
		PRINT << p->str;
	}
}

} /* end of namespace utility */
