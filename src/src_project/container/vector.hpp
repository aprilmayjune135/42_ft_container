#pragma once
#include "../iterator/RandomAccessIterator.hpp"
#include "../iterator/ReverseIterator.hpp"
#include "../iterator/lexicographic_compare.hpp"
#include <memory>
#include <cassert>
#include <algorithm>

namespace ft {

template < class T, class Alloc = std::allocator<T> >
class vector {
	public:
	/**** member types ****/
		typedef T						value_type;
		typedef Alloc					allocator_type;
		typedef value_type&				reference;
		typedef const value_type&		const_reference;
		typedef value_type*				pointer;
		typedef const value_type*		const_pointer;
		typedef RandomAccessIterator<value_type>				iterator;
		typedef RandomAccessIterator<const value_type>			const_iterator;
		typedef	ReverseIterator<iterator> 						reverse_iterator;
		typedef ReverseIterator<const_iterator>					const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type			difference_type;
		typedef std::size_t				size_type;
	
	/**** key protected member ****/
	protected:
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
		virtual ~vector();
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
		void	pop_back();
		iterator	insert(iterator position, const_reference val);
		void	insert(iterator position, size_type n, const_reference val);
		template <class InputIterator>
		void	insert(iterator position, InputIterator first, InputIterator last, typename iterator_traits<InputIterator>::iterator_category* dummy = 0);
		iterator	erase(iterator position);
		iterator	erase(iterator first, iterator last);
		void	swap(vector& x);
		void	clear();

	/**** allocator ****/
		allocator_type	get_allocator() const;

	private:
		void	constructElement(size_type index, const_reference val);
		void	destroyElement(size_type index);
		void	constructData(size_type position, size_type n, const_reference val);
		void	destroyData(size_type position, size_type n);
		void	allocateCapacity(size_type n);
		void	deallocateCapacity();
		void	destructAll();
		void	reallocateCapacity(size_type n);
		void	prepareAssign(size_type n);
		void	moveElement(size_type position_from, size_type position_to);
		void	moveElements(size_type position_from, size_type position_to, size_type n);
		void	insertWithCurrentCapacity(iterator position, size_type n, const_reference val);
		void	insertWithNewCapacity(iterator position, size_type n, const_reference val);
		template <class InputIterator>
		void	insertWithCurrentCapacity(iterator position, InputIterator first, InputIterator last, typename iterator_traits<InputIterator>::iterator_category* dummy = 0);
		template <class InputIterator>
		void	insertWithNewCapacity(iterator position, InputIterator first, InputIterator last, typename iterator_traits<InputIterator>::iterator_category* dummy = 0);

};

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
vector<T, Alloc>::vector(const vector& src):
allocator(src.allocator),
data(NULL),
data_size(0),
data_capacity(0) {
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
	assign(rhs.begin(), rhs.end());
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
		if (n > data_capacity) {
			reallocateCapacity(std::max(n, data_capacity * 2));
		}
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
	return *(data + data_size - 1);
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reference	vector<T, Alloc>::back() const {
	return *(data + data_size - 1);
}

/*********************************************/ 
/**					modifiers				**/ 
/*********************************************/
template <class T, class Alloc>
void	vector<T, Alloc>::assign(size_type n, const_reference val) {
	prepareAssign(n);
	constructData(0, n, val);
}

template <class T, class Alloc>
template <class InputIterator>
void	vector<T, Alloc>::assign(InputIterator first, InputIterator last, typename iterator_traits<InputIterator>::iterator_category* dummy) {
	size_type n = static_cast<size_type>(last - first);
	prepareAssign(n);
	for (size_type i = 0; i < n; ++i) {
		constructElement(i, *(first + i));
	}	
}

template <class T, class Alloc>
void	vector<T, Alloc>::push_back(const_reference val) {
	if (data_size == data_capacity) {
		size_type new_capacity;
		data_size == 0 ? new_capacity = 1 : new_capacity = data_capacity * 2;
		reallocateCapacity(new_capacity);
	}
	constructData(data_size, 1, val);
}

template <class T, class Alloc>
void	vector<T, Alloc>::pop_back() {
	if (data_size > 0) {
		destroyElement(data_size - 1);
	}
}

template <class T, class Alloc>
typename vector<T, Alloc>::iterator	vector<T, Alloc>::insert(iterator position, const_reference val) {
	difference_type pos = position - begin();
	insert(position, 1, val);
	return begin() + pos;
}

template <class T, class Alloc>
void	vector<T, Alloc>::insert(iterator position, size_type n, const_reference val) {
	if (data_size + n <= data_capacity) {
		insertWithCurrentCapacity(position, n, val);
	}
	else {
		insertWithNewCapacity(position, n, val);
	}
}

template <class T, class Alloc>
template <class InputIterator>
void	vector<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last, typename iterator_traits<InputIterator>::iterator_category* dummy) {
	size_type n = static_cast<size_type>(last - first);
	if (data_size + n <= data_capacity) {
		insertWithCurrentCapacity<InputIterator>(position, first, last, dummy);
	}
	else {
		insertWithNewCapacity<InputIterator>(position, first, last, dummy);
	}

}

template <class T, class Alloc>
typename vector<T, Alloc>::iterator	vector<T, Alloc>::erase(iterator position) {
	size_type	pos = static_cast<size_type>(position - begin());
	moveElements(pos + 1, pos, data_size - pos - 1);
	data_size--;
	return begin() + pos;
}

template <class T, class Alloc>
void	vector<T, Alloc>::swap(vector& x) {
	pointer		temp_data = data;
	size_type	temp_size = data_size;
	size_type	temp_capacity = data_capacity;
	data = x.data;
	data_size = x.data_size;
	data_capacity = x.data_capacity;
	x.data = temp_data;
	x.data_size = temp_size;
	x.data_capacity = temp_capacity;
}

template <class T, class Alloc>
typename vector<T, Alloc>::iterator	vector<T, Alloc>::erase(iterator first, iterator last) {
	size_type	pos = static_cast<size_type>(first - begin());
	size_type	n = static_cast<size_type>(last - first);
	size_type	size = data_size;
	for (size_type i = 0; i < n; ++i) {
		destroyElement(pos + i);
	}
	moveElements(pos + n, pos, size - pos - n);
	return begin() + pos;
}

template <class T, class Alloc>
void	vector<T, Alloc>::clear(){
	if (data_size > 0) {
		destroyData(0, data_size);
	}
	assert(data_size == 0);
}

/*********************************************/ 
/**					allocator				**/ 
/*********************************************/
template <class T, class Alloc>
typename vector<T, Alloc>::allocator_type	vector<T, Alloc>::get_allocator() const {
	return allocator;
}

/*********************************************/ 
/**		non-member function overload		**/ 
/*********************************************/
template <class T, class Alloc>
void	swap(vector<T, Alloc>& x, vector<T, Alloc>& y) {
	x.swap(y);
}

template <class T, class Alloc>
bool	operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
	if (lhs.size() != rhs.size()) {
		return false;
	}
	for (typename vector<T, Alloc>::size_type i = 0; i < lhs.size(); ++i) {
		if (lhs[i] != rhs[i]) {
			return false;
		}
	}
	return true;
}

template <class T, class Alloc>
bool	operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
	return !(lhs == rhs);
}

template <class T, class Alloc>
bool	operator<(const vector<T, Alloc>&lhs, const vector<T, Alloc>&rhs) {
	return lexicographic_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Alloc>
bool	operator<=(const vector<T, Alloc>&lhs, const vector<T, Alloc>&rhs) {
	return !(rhs < lhs);
}

template <class T, class Alloc>
bool	operator>(const vector<T, Alloc>&lhs, const vector<T, Alloc>&rhs) {
	return (rhs < lhs);
}

template <class T, class Alloc>
bool	operator>=(const vector<T, Alloc>&lhs, const vector<T, Alloc>&rhs) {
	return !(lhs < rhs);
}

/*********************************************/ 
/**			private member function			**/ 
/*********************************************/
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
void	vector<T, Alloc>::constructData(size_type position, size_type n, const_reference val) {
	for (size_type i = position; i < position + n; ++i) {
		constructElement(i, val);
	}
}

template <class T, class Alloc>
void	vector<T, Alloc>::destroyData(size_type position, size_type n) {
	for (size_type i = position; i < position + n; ++i) {
		destroyElement(i);
	}
}
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
	if (data) {
		clear();
		deallocateCapacity();
	}
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

/*
**	destroy all elements.
**	enlarge capacity if n is bigger than current capacity.
*/
template <class T, class Alloc>
void	vector<T, Alloc>::prepareAssign(size_type n) {
	if (n <= data_capacity) {
		clear();
	}
	else {
		destructAll();
		allocateCapacity(n);
	}
}

/*
**	move one element from old to new position.
**	content on new position is destroyed
**	no impact on data_size or data_capacity.
*/
template <class T, class Alloc>
void	vector<T, Alloc>::moveElement(size_type position_from, size_type position_to) {
	allocator.construct(data + position_to, data[position_from]);
	allocator.destroy(data + position_from);
}

/*
**	move n elements (starting from 'position_from') either left or right.
**	no impact on data_size or data_capacity.
*/
template <class T, class Alloc>
void	vector<T, Alloc>::moveElements(size_type position_from, size_type position_to, size_type n) {
	if (position_from > position_to) {
		for (size_type i = 0; i < n; ++i) {
			moveElement(position_from + i, position_to + i);
		}
	}
	else {
		size_type	position_end_new = position_to + n - 1;
		size_type	position_end_current = position_from + n - 1;
		for (size_type i = 0; i < n; ++i) {
			moveElement(position_end_current - i, position_end_new - i);
		}
	}
}

template <class T, class Alloc>
void	vector<T, Alloc>::insertWithCurrentCapacity(iterator position, size_type n, const_reference val) {
	size_type	pos_insert = static_cast<size_type>(position - begin());
	moveElements(pos_insert, pos_insert + n, data_size - pos_insert);
	for (size_type i = 0; i < n; ++i) {
		constructElement(pos_insert + i, val);
	}
}

template <class T, class Alloc>
void	vector<T, Alloc>::insertWithNewCapacity(iterator position, size_type n, const_reference val) {
	size_type	new_capacity = data_capacity + std::max(n, data_capacity);
	pointer	new_data = allocator.allocate(new_capacity);
	size_type	new_size = data_size + n;
	size_type	pos_insert = static_cast<size_type>(position - begin());
	size_type	pos_insert_end = pos_insert + n;
	size_type	pos_new_end = new_size - 1;
	size_type	pos_current_end = data_size - 1;
	for (size_type i = 0; i < pos_insert; ++i) {
		allocator.construct(new_data + i, *(data + i));
	}
	for (size_type i = pos_insert; i < pos_insert_end; ++i) {
		allocator.construct(new_data + i, val);
	}
	for (size_type i = pos_insert_end; i < new_size; ++i) {
		allocator.construct(new_data + i, *(data + i - n));
	}
	destructAll();
	data = new_data;
	data_size = new_size;
	data_capacity = new_capacity;
}


template <class T, class Alloc>
template <class InputIterator>
void	vector<T, Alloc>::insertWithCurrentCapacity(iterator position, InputIterator first, InputIterator last, typename iterator_traits<InputIterator>::iterator_category* dummy) {
	size_type	n = static_cast<size_type>(last - first);
	size_type	pos_insert = static_cast<size_type>(position - begin());
	moveElements(pos_insert, pos_insert + n, data_size - pos_insert);
	for (size_type i = 0; i < n; ++i) {
		constructElement(pos_insert + i, *(first + i));
	}
}

template <class T, class Alloc>
template <class InputIterator>
void	vector<T, Alloc>::insertWithNewCapacity(iterator position, InputIterator first, InputIterator last, typename iterator_traits<InputIterator>::iterator_category* dummy) {
	size_type	n = static_cast<size_type>(last - first);
	size_type	new_capacity = data_capacity + std::max(n, data_capacity);
	pointer	new_data = allocator.allocate(new_capacity);
	size_type	new_size = data_size + n;
	size_type	pos_insert = static_cast<size_type>(position - begin());
	size_type	pos_insert_end = pos_insert + n;
	size_type	pos_new_end = new_size - 1;
	size_type	pos_current_end = data_size - 1;
	for (size_type i = 0; i < pos_insert; ++i) {
		allocator.construct(new_data + i, *(data + i));
	}
	for (size_type i = pos_insert; i < pos_insert_end; ++i) {
		allocator.construct(new_data + i, *(first + i - pos_insert));
	}
	for (size_type i = pos_insert_end; i < new_size; ++i) {
		allocator.construct(new_data + i, *(data + i - n));
	}
	destructAll();
	data = new_data;
	data_size = new_size;
	data_capacity = new_capacity;
}


} /* end of namespace ft */
