#pragma once
#include <memory>
#include <cassert>
#include "../iterator/RandomAccessIterator.hpp"
#include "../iterator/ReverseIterator.hpp"

namespace ft {

template < class T, class Alloc = std::allocator<T> >
class vector {
	public:
	/**** typedef ****/
		typedef T						value_type;
		typedef Alloc					allocator_type;
		typedef value_type&				reference;
		typedef const value_type&		const_reference;
		typedef value_type*				pointer;
		typedef const value_type*		const_pointer;

		typedef RandomAccessIterator<T>		iterator;
		typedef const iterator				const_iterator;
		typedef	ReverseIterator<iterator> 	reverse_iterator;
		typedef const reverse_iterator		const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type			difference_type;
		typedef std::size_t							size_type;
	
	/**** key private member ****/
	private:
		allocator_type	allocator;
		pointer			data;
		size_type		data_size;
		size_type		data_capacity;
	
	public:
	/**** constructor & destructor & operator ****/
		explicit vector(const allocator_type& alloc = allocator_type());
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
		template<class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
		vector(const vector& src);
		~vector();
		vector&	operator=(const vector& rhs);

	/**** iterator ****/
		iterator				begin();
		const_iterator			begin() const;
		iterator				end();
		const_iterator			end() const;
		reverse_iterator		rbegin();
		const_reverse_iterator	rbegin() const;
		iterator				rend();
		const_reverse_iterator	rend() const;

	
	/**** capacity ****/
		size_type	size() const;
		size_type	max_size() const;
		void		resize(size_type n, value_type val = value_type());
		size_type	capacity() const;
		bool		empty() const;
		void		reserve(size_type n);

	/**** element access ****/

	/**** modifiers ****/
		void	clear();

	/**** allocator ****/

	/**** non-member function overloads ****/

	/**** template specialization ****/

	private:
		void	destroyElement(size_type index);
		void	destroyData();
		void	deallocateData();

	

};

/*****************************************************/ 
/**			constructor	& destructor & operator		**/ 
/*****************************************************/
/* empty/default constructor */
template< class T, class Alloc >
vector<T, Alloc>::vector(const allocator_type& alloc):
allocator(alloc),
data(NULL),
data_size(0),
data_capacity(0) {}

/* fill constructor */
template< class T, class Alloc >
vector<T, Alloc>::vector(size_type n, const value_type& val, const allocator_type& alloc):
allocator(alloc),
data(NULL),
data_size(n),
data_capacity(n) {
	//TODO: call assign()
}

/* range constructor */
template< class T, class Alloc >
template< class InputIterator >
vector<T, Alloc>::vector(InputIterator first, InputIterator last, const allocator_type& alloc) :
allocator(alloc) {
	// TODO:
}

/* copy constructor */
template< class T, class Alloc >
vector<T, Alloc>::vector(const vector& src) {
	// TODO:
}

/* destructor */
template< class T, class Alloc >
vector<T, Alloc>::~vector() {
	deallocateData();
}

/* operator */
template< class T, class Alloc >
vector<T, Alloc>&	vector<T, Alloc>::operator=(const vector& rhs){
	// TODO:
	return *this;
}


/*********************************************/ 
/**					iterator				**/ 
/*********************************************/
template< class T, class Alloc >
typename vector<T, Alloc>::iterator				vector<T, Alloc>::begin() { return iterator(data); }

template< class T, class Alloc >
typename vector<T, Alloc>::const_iterator			vector<T, Alloc>::begin() const { return const_iterator(data); }

template< class T, class Alloc >
typename vector<T, Alloc>::iterator				vector<T, Alloc>::end() { return iterator(data + data_size); }

template< class T, class Alloc >
typename vector<T, Alloc>::const_iterator			vector<T, Alloc>::end() const { return const_iterator(data + data_size); }

template< class T, class Alloc >
typename vector<T, Alloc>::reverse_iterator		vector<T, Alloc>::rbegin() { return reverse_iterator(data + data_size); }

template< class T, class Alloc >
typename vector<T, Alloc>::const_reverse_iterator	vector<T, Alloc>::rbegin() const { return const_reverse_iterator(data + data_size); }

template< class T, class Alloc >
typename vector<T, Alloc>::iterator				vector<T, Alloc>::rend() { return reverse_iterator(data); }

template< class T, class Alloc >
typename vector<T, Alloc>::const_reverse_iterator	vector<T, Alloc>::rend() const { return const_reverse_iterator(data); }


/*********************************************/ 
/**					capacity				**/ 
/*********************************************/
template< class T, class Alloc>
typename vector<T, Alloc>::size_type	vector<T, Alloc>::size() const{
	return data_size;
}

template< class T, class Alloc>
typename vector<T, Alloc>::size_type	vector<T, Alloc>::max_size() const{
	return allocator.max_size();
}

template< class T, class Alloc>
void	vector<T, Alloc>::resize(size_type n, value_type val){
	// TODO
}

template< class T, class Alloc>
typename vector<T, Alloc>::size_type	vector<T, Alloc>::capacity() const{
	return data_capacity;
}

template< class T, class Alloc>
bool	vector<T, Alloc>::empty() const{
	return data_size == 0;
}

template< class T, class Alloc>
void	vector<T, Alloc>::reserve(size_type n){
	if (n > data_capacity)
	{
		pointer new_data = allocator.allocate(n);
		// TODO: assign
		deallocateData();
		data = new_data;
		data_capacity = n;
	}
}


/*********************************************/ 
/**					modifiers				**/ 
/*********************************************/
template< class T, class Alloc >
void	vector<T, Alloc>::clear(){
	size_type	n = data_size;
	for (size_type i = 0; i < n; ++i) {
		destroyElement(i);
	}
	assert(data_size == 0);
}


/*********************************************/ 
/**			private member function			**/ 
/*********************************************/
template< class T, class Alloc >
void	vector<T, Alloc>::destroyElement(size_type index) {
	assert(index < data_size);
	allocator.destroy(data + index);
	data_size--;
}

template< class T, class Alloc >
void	vector<T, Alloc>::deallocateData() {
	clear();
	allocator.deallocate(data, data_capacity);
	data = NULL;
}


} /* end of namespace ft */
