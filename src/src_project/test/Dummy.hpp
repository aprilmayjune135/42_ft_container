#pragma once
#include <iostream>

template <class T>
class Dummy {
	public:
		Dummy() {};
		Dummy(const Dummy& src) { *this = src; };
		Dummy(const T& t): data(t) {};
		Dummy&	operator=(const Dummy& src) {
			data = src.data;
			return *this;
		};
		~Dummy() {};
		
		friend std::ostream&	operator<<(std::ostream& o, const Dummy& dummy) { 
			o << dummy.data;
			return o;
		};

	private:
		T	data;

};


