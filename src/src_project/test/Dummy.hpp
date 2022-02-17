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
		
		bool	operator==(const Dummy& src) const {
			return (data == src.data);
		}

		bool	operator!=(const Dummy& src) const {
			return !(data == src.data);
		}

		bool	operator<(const Dummy& src) const {
			return (data < src.data);
		}

		operator Dummy<const T>() const {
			return data;
		}

		friend std::ostream&	operator<<(std::ostream& o, const Dummy& dummy) { 
			o << dummy.data;
			return o;
		};

	private:
		T	data;

};


typedef	Dummy<int>				dummy_type;
typedef	Dummy<dummy_type>		dummy_type_2D;

