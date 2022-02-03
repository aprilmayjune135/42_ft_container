#pragma once
#include "../iterator/RandomAccessIterator.hpp"
#include "../iterator/ReverseIterator.hpp"
#include "../iterator/iterator_traits.hpp"
#include "../utility/utility.hpp"
#include <memory>
#include <cassert>
#include <type_traits> //TODO: to delete

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
		explicit vector(size_type n, const_reference val = value_type(), const allocator_type& alloc = allocator_type());
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename iterator_traits<InputIterator>::iterator_category* dummy = 0);
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
		reverse_iterator		rend();
		const_reverse_iterator	rend() const;

	
	/**** capacity ****/
		size_type	size() const;
		size_type	max_size() const;
		void		resize(size_type n, value_type val = value_type());
		size_type	capacity() const;
		bool		empty() const;
		void		reserve(size_type n);

	/**** element access ****/
		reference	operator[](size_type n);
		const_reference	operator[](size_type n) const;
		reference	at(size_type n);
		const_reference	at(size_type n) const;
		reference	front();
		const_reference	front() const;
		reference	back();
		const_reference	back() const;

	/**** modifiers ****/
		void	assign(size_type n, const_reference val);
		template <class InputIterator>
		void	assign(InputIterator first, InputIterator last, typename iterator_traits<InputIterator>::iterator_category* dummy = 0);
		void	push_back(const_reference val);
		void	clear();

	/**** allocator ****/

	/**** non-member function overloads ****/

	/**** template specialization ****/

	private:
		void	allocateCapacity(size_type n);
		void	deallocateCapacity();
		void	destructAll();
		void	reallocateCapacity(size_type n);
		void	constructElement(size_type index, const_reference val);
		void	destroyElement(size_type index);
		void	constructData(size_type pos, size_type n, const_reference val);
		void	destroyData(size_type pos, size_type n);

};

template <class T, class Alloc>
template <class InputIterator>
void	vector<T, Alloc>::assign(InputIterator first, InputIterator last, typename iterator_traits<InputIterator>::iterator_category* dummy) {
	if (data) {
		destructAll();
	}
	size_type n = static_cast<size_type>(last - first);
	allocateCapacity(n);
	for (size_type i = 0; i < n; ++i) {
		constructElement(i, *(first + i));
	}	
}


/*****************************************************/ 
/**			constructor	& destructor & operator		**/ 
/*****************************************************/
/* empty/default constructor */
template <class T, class Alloc>
vector<T, Alloc>::vector(const allocator_type& alloc):
allocator(alloc),
data(NULL),
data_size(0),
data_capacity(0) {}

/* fill constructor */
template <class T, class Alloc>
vector<T, Alloc>::vector(size_type n, const_reference val, const allocator_type& alloc):
allocator(alloc),
data(NULL),
data_size(0),
data_capacity(0) {
	assign(n, val);
}

/* range constructor */
template <class T, class Alloc>
template <class InputIterator>
vector<T, Alloc>::vector(InputIterator first, InputIterator last, const allocator_type& alloc, typename iterator_traits<InputIterator>::iterator_category* dummy) :
allocator(alloc),
data(NULL),
data_size(0),
data_capacity(0) {
	assign<InputIterator>(first, last);
}

/* copy constructor */
template <class T, class Alloc>
vector<T, Alloc>::vector(const vector& src) {
	*this = src;
}

/* destructor */
template <class T, class Alloc>
vector<T, Alloc>::~vector() {
	destructAll();
}

/* operator */
template <class T, class Alloc>
vector<T, Alloc>&	vector<T, Alloc>::operator=(const vector& rhs){
	// TODO:
	return *this;
}


/*********************************************/ 
/**					iterator				**/ 
/*********************************************/
template <class T, class Alloc>
typename vector<T, Alloc>::iterator	vector<T, Alloc>::begin() { return iterator(data); }

template <class T, class Alloc>
typename vector<T, Alloc>::const_iterator	vector<T, Alloc>::begin() const { return const_iterator(data); }

template <class T, class Alloc>
typename vector<T, Alloc>::iterator		vector<T, Alloc>::end() { return iterator(data + data_size); }

template <class T, class Alloc>
typename vector<T, Alloc>::const_iterator	vector<T, Alloc>::end() const { return const_iterator(data + data_size); }

template <class T, class Alloc>
typename vector<T, Alloc>::reverse_iterator	vector<T, Alloc>::rbegin() { return reverse_iterator(end()); }

template <class T, class Alloc>
typename vector<T, Alloc>::const_reverse_iterator	vector<T, Alloc>::rbegin() const { return const_reverse_iterator(end()); }

template <class T, class Alloc>
typename vector<T, Alloc>::reverse_iterator		vector<T, Alloc>::rend() { return reverse_iterator(begin()); }

template <class T, class Alloc>
typename vector<T, Alloc>::const_reverse_iterator	vector<T, Alloc>::rend() const { return const_reverse_iterator(begin()); }


/*********************************************/ 
/**					capacity				**/ 
/*********************************************/
template <class T, class Alloc>
typename vector<T, Alloc>::size_type	vector<T, Alloc>::size() const{
	return data_size;
}

template <class T, class Alloc>
typename vector<T, Alloc>::size_type	vector<T, Alloc>::max_size() const{
	return allocator.max_size();
}

template <class T, class Alloc>
void	vector<T, Alloc>::resize(size_type n, value_type val){
	if (n < data_size) {
		destroyData(n, data_size - n);
	}
	else {
		reserve(n);
		constructData(data_size, n - data_size, val);
	}
}

template <class T, class Alloc>
typename vector<T, Alloc>::size_type	vector<T, Alloc>::capacity() const{
	return data_capacity;
}

template <class T, class Alloc>
bool	vector<T, Alloc>::empty() const{
	return data_size == 0;
}

template <class T, class Alloc>
void	vector<T, Alloc>::reserve(size_type n){
	if (n > data_capacity) {
		reallocateCapacity(n);
	}
}


/*********************************************/ 
/**				element access				**/ 
/*********************************************/
template <class T, class Alloc>
typename vector<T, Alloc>::reference	vector<T, Alloc>::operator[](size_type n) {
	return *(data + n);
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reference	vector<T, Alloc>::operator[](size_type n) const {
	return *(data + n);
}

template <class T, class Alloc>
typename vector<T, Alloc>::reference	vector<T, Alloc>::at(size_type n) {
	// TODO: add throw exception
	// if (n >= size) {
	// 
	// }
	return *(data + n);
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reference	vector<T, Alloc>::at(size_type n) const {
	// TODO: add throw exception
	// if (n >= size) {
	// 
	// }
	return *(data + n);
}

template <class T, class Alloc>
typename vector<T, Alloc>::reference	vector<T, Alloc>::front() {
	return *data;
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reference	vector<T, Alloc>::front() const {
	return *data;
}

template <class T, class Alloc>
typename vector<T, Alloc>::reference	vector<T, Alloc>::back() {
	return *(data + data_size);
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reference	vector<T, Alloc>::back() const {
	return *(data + data_size);
}

/*********************************************/ 
/**					modifiers				**/ 
/*********************************************/
template <class T, class Alloc>
void	vector<T, Alloc>::assign(size_type n, const_reference val) {
	if (data) {
		destructAll();
	}
	allocateCapacity(n);
	constructData(0, n, val);
}

template <class T, class Alloc>
void	vector<T, Alloc>::clear(){
	if (data_size > 0) {
		destroyData(0, data_size);
	}
	assert(data_size == 0);
}

/*********************************************/ 
/**			private member function			**/ 
/*********************************************/
template <class T, class Alloc>
void	vector<T, Alloc>::allocateCapacity(size_type n) {
	data = allocator.allocate(n);
	data_capacity = n;
}

template <class T, class Alloc>
void	vector<T, Alloc>::deallocateCapacity() {
	allocator.deallocate(data, data_capacity);
	data_capacity = 0;
	data = NULL;
}


template <class T, class Alloc>
void	vector<T, Alloc>::destructAll() {
	clear();
	deallocateCapacity();
}

template <class T, class Alloc>
void	vector<T, Alloc>::reallocateCapacity(size_type n) {
	size_type	current_size = data_size;
	pointer	new_data = allocator.allocate(n);
	for (size_type i = 0; i < current_size; ++i) {
		allocator.construct(new_data + i, *(data + i));
	}
	destructAll();
	data = new_data;
	data_size = current_size;
	data_capacity = n;
}

template <class T, class Alloc>
void	vector<T, Alloc>::constructElement(size_type index, const_reference val) {
	allocator.construct(data + index, val);
	data_size++;
}

template <class T, class Alloc>
void	vector<T, Alloc>::destroyElement(size_type index) {
	allocator.destroy(data + index);
	data_size--;
}

template <class T, class Alloc>
void	vector<T, Alloc>::constructData(size_type pos, size_type n, const_reference val) {
	for (size_type i = pos; i < pos + n; ++i) {
		constructElement(i, val);
	}
}

template <class T, class Alloc>
void	vector<T, Alloc>::destroyData(size_type pos, size_type n) {
	for (size_type i = pos; i < pos + n; ++i) {
		destroyElement(i);
	}
}


} /* end of namespace ft */
