#pragma once
#include "vector.hpp"

namespace ft {

template <class T, class Container = ft::vector<T> >
class stack {
	/*****************************************************/ 
	/**					member types					**/ 
	/*****************************************************/
	public:
		typedef T			value_type;
		typedef Container	container_type;
		typedef	std::size_t	size_type;

	/*****************************************************/ 
	/**					key members						**/ 
	/*****************************************************/
	protected:
		container_type	container;

	/*****************************************************/ 
	/**				public member function				**/ 
	/*****************************************************/
	public:
		explicit	stack(const container_type& ctnr = container_type()):
			container(ctnr) {};

		bool	empty() const { return container.empty(); };

		size_type	size() const { return container.size(); };

		value_type&	top() { return container.back(); };
		const value_type&	top() const { return container.back(); };

		void	push(const value_type& val) { return container.push_back(val); };

		void	pop() { return container.pop_back(); };

	/*****************************************************/ 
	/**			non-member function overload			**/ 
	/*****************************************************/
		friend	bool	operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
			return lhs.container == rhs.container;
		};

		friend	bool	operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
			return lhs.container < rhs.container;
		};

}; /* end of class stack */

/*****************************************************/ 
/**			non-member function overload			**/ 
/*****************************************************/
template <class T, class Container>
bool	operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
	return !(lhs == rhs);
}

template <class T, class Container>
bool	operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
	return !(rhs < lhs);
}

template <class T, class Container>
bool	operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
	return rhs < lhs;
}

template <class T, class Container>
bool	operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
	return !(lhs < rhs);
}

} /* end of namespace ft */
