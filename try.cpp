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

void	printCapacityInfo(std::vector<int> const & v) {
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
class AppleChik : public Apple<T> {
	public:
		AppleChik();
		AppleChik(T n): Apple<T>(n) {};
		AppleChik&	operator=(const AppleChik& src) {
			this->a = src.a;
			return *this;
		};
		bool	operator==(const AppleChik& rhs) const {return this->a == rhs.a;};
		AppleChik&	operator++() { this->a += 100; return *this; };

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
	// std::vector<int>	vector;
	// typedef typename std::vector<int>::iterator it;
	// typedef typename std::vector<int>::reverse_iterator rev_it;
	// for (int i = 0; i < 10; i++) {vector.push_back(i);}
	// for (it i = vector.begin(); i != vector.end(); ++i) {
	// 	std::cout << *i << " ";
	// }
	// std::cout << '\n';

	// std::vector<double>	vector_double;
	// typedef typename std::vector<double>::iterator it_double;
	// typedef typename std::vector<double>::reverse_iterator rev_it_double;
	// for (int i = 0; i < 10; i++) {vector_double.push_back(i + 0.5);}
	// for (it_double i = vector_double.begin(); i != vector_double.end(); ++i) {
	// 	std::cout << *i << " ";
	// }
	// std::cout << '\n';

	// rev_it	r_begin(vector.begin());
	// rev_it	r_end(vector.end());
	// rev_it	r_end_double(r_end + 2);
	// rev_it	r_begin_double(r_begin - 2);
	// for (rev_it r_i = r_end_double; r_i != r_begin_double; ++r_i) {
	// 	std::cout << *r_i << "-" << *r_i.base() << " ";
	// }

	std::vector<int> lemon(10, 14);
	printVector(lemon);
	printCapacityInfo(lemon);
	lemon.resize(2, 111);
	printVector(lemon);
	printCapacityInfo(lemon);
	lemon.resize(20, 111);
	printVector(lemon);
	printCapacityInfo(lemon);


	return 0;
}
