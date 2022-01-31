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

template<class T>
class Apple {
	protected:
		T	a;
	public:
		Apple();
		Apple(T n): a(n) {};
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

template<class T>
class AppleTje : public Apple<T> {
	public:
		AppleTje();
		AppleTje(T n): Apple<T>(n) {};
		AppleTje&	operator=(const AppleTje& src) {
			this->a = src.a;
			return *this;
		};
		bool	operator==(const AppleTje& rhs) const {return this->a == rhs.a;};
		AppleTje&	operator++() { this->a += 100; return *this; };

};

template<class T>
void	increaseApple(Apple<T>* apple) {
	++(*apple);
	apple->printApple();
}

AppleTje<int>	createApple() {
	return AppleTje<int>(18);
}

int main() {

	AppleTje<int>	piggy = createApple();
	piggy.printApple();
	// std::vector<int> v {50, 40, 30, 20, 10};
	// std::vector<int>::const_iterator	i_1 = v.begin();
	// std::vector<int>::const_iterator	i_2 = v.begin() + 2;
	// std::cout << (i_2 - i_1) << '\n';

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
