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

class Apple {
	protected:
		int	a;
	public:
		Apple();
		Apple(int n): a(n) {};
		Apple(const Apple&	src) {
			a = src.a;
			std::cout << "copy-constructor called!\n";
		};
		Apple&	operator=(const Apple& rhs) {
			a = rhs.a * 2;
			std::cout << "calling operator=!\n";
			return *this;
		};
		virtual ~Apple() {};
		virtual Apple&	operator++() { a += 2; return *this; };
		bool	operator==(const Apple& rhs) const {return a == rhs.a;};
		void	printApple() const {std::cout << a << '\n';};
};

class AppleTje : public Apple {
	public:
		AppleTje();
		AppleTje(int n): Apple(n) { a = n; };
		bool	operator==(const AppleTje& rhs) const {return a == rhs.a;};
		AppleTje&	operator++() { a += 100; return *this; };

};

void	increaseApple(Apple* apple)
{
	++(*apple);
	apple->printApple();
}

int main() {
	std::vector<int> v {5, 4, 3, 2, 1};
	std::vector<int>::const_iterator	i_1 = v.begin();
	std::vector<int>::const_iterator	i_2 = v.begin() + 1;
	std::cout << (i_1 < i_2) << '\n';
	//std::vector<int> lemon(5, 14);
	//printVector(lemon);
	//printCapacity(lemon);
	//lemon.reserve(2);
	//printVector(lemon);
	//printCapacity(lemon);
	//lemon.reserve(10);
	//printVector(lemon);
	//printCapacity(lemon);
	//return 0;
}
