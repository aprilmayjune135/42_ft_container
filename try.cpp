#include <iostream>
#include <vector>

template< class T>
class Lemon {
public:
	T		data;
	void	set(T value) {data = value;}
	void	increaseTwo();
private:
	void	decrease()	{data--;}
	void	increase()	{data++;}

};

template< class T>
void	Lemon<T>::increaseTwo() {
	T value = 5;
	set(value);
	increase();
	std::cout << data << '\n';
}

void	printVector(std::vector<int> const & v) {
	for (int i : v) {
		std::cout << i << " ";
	}
	std::cout << '\n';
}

void	printCapacity(std::vector<int> const & v) {
	std::cout << "size " << v.size() << " | capacity " << v.capacity() << " | max_size " << v.max_size() << '\n';
}

int main() {
	std::vector<int> lemon(5, 14);
	printVector(lemon);
	printCapacity(lemon);
	lemon.reserve(2);
	printVector(lemon);
	printCapacity(lemon);
	lemon.reserve(10);
	printVector(lemon);
	printCapacity(lemon);
	return 0;
}
