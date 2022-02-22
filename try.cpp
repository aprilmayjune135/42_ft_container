#include <iostream>
#include <vector>
#include <map>

int main() {
	typedef std::map<int, char> 		map_type;
	typedef typename map_type::iterator	iterator;
	map_type map;
	for (int i = 5; i > 0; --i) {
		map[i] = 'a' + i;
	}
	for (iterator it = map.begin(); it != map.end(); ++it) {
		std::cout << it->first << ' ';
	}
	return 0;
}
