#pragma once
#include "../iterator/RandomAccessIterator.hpp"
#include "../iterator/ReverseIterator.hpp"
#include "../iterator/lexicographic_compare.hpp"
#include "../utility/utility.hpp"
#include <memory>
#include <cassert>
#include <algorithm>
#include <stdexcept>

namespace ft {

template < class T, class Alloc = std::allocator<T> >
class vector {
	/*****************************************************/ 
	/**					member types					**/ 
	/*****************************************************/
	public:
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
	
	/*****************************************************/ 
	/**					key members						**/ 
	/*****************************************************/
	protected:
		allocator_type	allocator;
		pointer			data;
		size_type		data_size;
		size_type		data_capacity;
	
	public:
	/*****************************************************/ 
	/**			constructor	& destructor & operator		**/ 
	/*****************************************************/
		/* empty/default constructor */
		explicit vector(const allocator_type& alloc = allocator_type()):
			allocator(alloc),
			data(NULL),
			data_size(0),
			data_capacity(0) {};

		/* fill constructor */
		explicit vector(size_type n, const_reference val = value_type(), const allocator_type& alloc = allocator_type()):
			allocator(alloc),
			data(NULL),
			data_size(0),
			data_capacity(0) {
				try {
					assign(n, val);
				}
				catch (const std::exception& e) {
					destructAll();
					throw e;
				}
			};

		/* range constructor */
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename iterator_traits<InputIterator>::iterator_category* dummy = 0):
			allocator(alloc),
			data(NULL),
			data_size(0),
			data_capacity(0) {
				try {
					assign<InputIterator>(first, last);
				}
				catch (const std::exception& e) {
					destructAll();
					throw e;
				}
			};

		/* copy constructor */
		vector(const vector& src) :
			allocator(src.allocator),
			data(NULL),
			data_size(0),
			data_capacity(0) {
				try {
					*this = src;
				}
				catch (const std::exception& e) {
					destructAll();
					throw e;
				}
			};

		/* destructor */
		virtual ~vector()  {
			destructAll();
		};

		/* operator */
		vector&	operator=(const vector& rhs) {
			assign(rhs.begin(), rhs.end());
			return *this;
		};

	/*****************************************************/ 
	/**						iterator					**/ 
	/*****************************************************/
		iterator				begin()  { return iterator(data); };
		const_iterator			begin() const  { return const_iterator(data); };
		iterator				end()  { return iterator(data + data_size); };
		const_iterator			end() const  { return const_iterator(data + data_size); };
		reverse_iterator		rbegin()  { return reverse_iterator(end()); };
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); };
		reverse_iterator		rend() { return reverse_iterator(begin()); };
		const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); };
	
	/*****************************************************/ 
	/**						capacity					**/ 
	/*****************************************************/
		size_type	size() const { return data_size; };

		size_type	max_size() const { return allocator.max_size(); };
		
		void		resize(size_type n, value_type val = value_type()) {
			if (n < data_size) {
				destroyData(n, data_size - n);
			}
			else {
				if (n > data_capacity) {
					reallocateCapacity(std::max(n, data_capacity * 2));
				}
				constructData(data_size, n - data_size, val);
			}
		};

		size_type	capacity() const { return data_capacity; };

		bool		empty() const { return data_size == 0; };

		void		reserve(size_type n) {
			if (n > data_capacity) {
				reallocateCapacity(n);
			}
		};

	/*****************************************************/ 
	/**					element access					**/ 
	/*****************************************************/
		reference	operator[](size_type n) { return *(data + n); };
		const_reference	operator[](size_type n) const { return *(data + n); };

		reference	at(size_type n) {
			if (n >= data_size) {
				throw std::out_of_range("vector.at(size_t n): n exceeds container size.");
			}
			return *(data + n);
		};
		const_reference	at(size_type n) const {
			if (n >= data_size) {
				throw std::out_of_range("vector.at(size_t n): n exceeds container size.");
			}
			return *(data + n);
		};

		reference	front() { return *data; };
		const_reference	front() const { return *data; };

		reference	back() { return *(data + data_size - 1); };
		const_reference	back() const { return *(data + data_size - 1); };

	/*****************************************************/ 
	/**						modifiers					**/ 
	/*****************************************************/
		/* assign */
		void	assign(size_type n, const_reference val) {
			prepareAssign(n);
			constructData(0, n, val);
		};

		template <class InputIterator>
		void	assign(InputIterator first, InputIterator last, typename iterator_traits<InputIterator>::iterator_category* dummy = 0) {
			size_type n = iteratorDistance(first, last);
			prepareAssign(n);
			for (size_type i = 0; i < n; ++i) {
				constructElement(i, *first);
				++first;
			}	
		};

		/* push_back */
		void	push_back(const_reference val) {
			if (data_size == data_capacity) {
				size_type new_capacity;
				data_size == 0 ? new_capacity = 1 : new_capacity = data_capacity * 2;
				reallocateCapacity(new_capacity);
			}
			constructData(data_size, 1, val);
		};

		/* pop_back */
		void	pop_back() {
			if (data_size > 0) {
				destroyElement(data_size - 1);
			}
		};

		/* insert */
		iterator	insert(iterator position, const_reference val) {
			difference_type pos = position - begin();
			insert(position, 1, val);
			return begin() + pos;
		};

		void	insert(iterator position, size_type n, const_reference val) {
			if (data_size + n <= data_capacity) {
				insertWithCurrentCapacity(position, n, val);
			}
			else {
				insertWithNewCapacity(position, n, val);
			}
		};

		template <class InputIterator>
		void	insert(iterator position, InputIterator first, InputIterator last, typename iterator_traits<InputIterator>::iterator_category* dummy = 0) {
			size_type n = iteratorDistance(first, last);
			if (data_size + n <= data_capacity) {
				insertWithCurrentCapacity<InputIterator>(position, first, last, dummy);
			}
			else {
				insertWithNewCapacity<InputIterator>(position, first, last, dummy);
			}
		};

		/* erase */
		iterator	erase(iterator position) {
			size_type	pos = static_cast<size_type>(position - begin());
			moveElements(pos + 1, pos, data_size - pos - 1);
			data_size--;
			return begin() + pos;
		};

		iterator	erase(iterator first, iterator last) {
			size_type	pos = static_cast<size_type>(first - begin());
			size_type	n = static_cast<size_type>(last - first);
			size_type	size = data_size;
			for (size_type i = 0; i < n; ++i) {
				destroyElement(pos + i);
			}
			moveElements(pos + n, pos, size - pos - n);
			return begin() + pos;
		};

		/* swap */
		void	swap(vector& x) {
			pointer		temp_data = data;
			size_type	temp_size = data_size;
			size_type	temp_capacity = data_capacity;
			data = x.data;
			data_size = x.data_size;
			data_capacity = x.data_capacity;
			x.data = temp_data;
			x.data_size = temp_size;
			x.data_capacity = temp_capacity;
		};

		/* clear */
		void	clear() {
			if (data_size > 0) {
				destroyData(0, data_size);
			}
			assert(data_size == 0);
		};

	/*****************************************************/ 
	/**						allocator					**/ 
	/*****************************************************/
		allocator_type	get_allocator() const { return allocator; };

	/*****************************************************/ 
	/**				private member function				**/ 
	/*****************************************************/
	private:
		void	constructElement(size_type index, const_reference val) {
			allocator.construct(data + index, val);
			data_size++;
		};

		void	destroyElement(size_type index) {
			allocator.destroy(data + index);
			data_size--;
		};
		
		void	constructData(size_type position, size_type n, const_reference val) {
			for (size_type i = position; i < position + n; ++i) {
				constructElement(i, val);
			}
		};
		
		void	destroyData(size_type position, size_type n) {
			for (size_type i = position; i < position + n; ++i) {
				destroyElement(i);
			}
		};
		
		pointer	allocateHelper(size_type n) {
			if (n > max_size()) {
				throw std::length_error("vector: allocate target size is larger than max_size.");
			}
			return allocator.allocate(n);
		};
		
		void	allocateCapacity(size_type n) {
			data = allocateHelper(n);
			data_capacity = n;
		};
		
		void	deallocateCapacity() {
			allocator.deallocate(data, data_capacity);
			data_capacity = 0;
			data = NULL;
		};
		
		void	destructAll() {
			if (data) {
				clear();
				deallocateCapacity();
			}
		};
		
		void	reallocateCapacity(size_type n) {
			size_type	current_size = data_size;
			pointer	new_data = allocateHelper(n);
			for (size_type i = 0; i < current_size; ++i) {
				allocator.construct(new_data + i, *(data + i));
			}
			destructAll();
			data = new_data;
			data_size = current_size;
			data_capacity = n;
		};
		
		/*
		**	destroy all elements.
		**	enlarge capacity if n is bigger than current capacity.
		*/
		void	prepareAssign(size_type n) {
			if (n <= data_capacity) {
				clear();
			}
			else {
				destructAll();
				allocateCapacity(n);
			}
		};
		
		/*
		**	move one element from old to new position.
		**	content on new position is destroyed
		**	no impact on data_size or data_capacity.
		*/
		void	moveElement(size_type position_from, size_type position_to) {
			allocator.construct(data + position_to, data[position_from]);
			allocator.destroy(data + position_from);
		};
		
		/*
		**	move n elements (starting from 'position_from') either left or right.
		**	no impact on data_size or data_capacity.
		*/
		void	moveElements(size_type position_from, size_type position_to, size_type n) {
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
		};
		
		void	insertWithCurrentCapacity(iterator position, size_type n, const_reference val) {
			size_type	pos_insert = static_cast<size_type>(position - begin());
			moveElements(pos_insert, pos_insert + n, data_size - pos_insert);
			for (size_type i = 0; i < n; ++i) {
				constructElement(pos_insert + i, val);
			}
		};
		
		void	insertWithNewCapacity(iterator position, size_type n, const_reference val) {
			size_type	new_capacity = data_capacity + std::max(n, data_capacity);
			pointer		new_data = allocateHelper(new_capacity);
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
		};
		
		template <class InputIterator>
		void	insertWithCurrentCapacity(iterator position, InputIterator first, InputIterator last, typename 
		iterator_traits<InputIterator>::iterator_category* dummy = 0) {
			size_type	n = iteratorDistance(first, last);
			size_type	pos_insert = static_cast<size_type>(position - begin());
			moveElements(pos_insert, pos_insert + n, data_size - pos_insert);
			for (size_type i = 0; i < n; ++i) {
				constructElement(pos_insert + i, *first);
				++first;
			}
		};
		
		template <class InputIterator>
		void	insertWithNewCapacity(iterator position, InputIterator first, InputIterator last, typename 
		iterator_traits<InputIterator>::iterator_category* dummy = 0) {
			size_type	n = iteratorDistance(first, last);
			size_type	new_capacity = data_capacity + std::max(n, data_capacity);
			pointer		new_data = allocateHelper(new_capacity);
			size_type	new_size = data_size + n;
			size_type	pos_insert = static_cast<size_type>(position - begin());
			size_type	pos_insert_end = pos_insert + n;
			size_type	pos_new_end = new_size - 1;
			size_type	pos_current_end = data_size - 1;
			for (size_type i = 0; i < pos_insert; ++i) {
				allocator.construct(new_data + i, *(data + i));
			}
			for (size_type i = pos_insert; i < pos_insert_end; ++i) {
				allocator.construct(new_data + i, *first);
				++first;
			}
			for (size_type i = pos_insert_end; i < new_size; ++i) {
				allocator.construct(new_data + i, *(data + i - n));
			}
			destructAll();
			data = new_data;
			data_size = new_size;
			data_capacity = new_capacity;
		};

};  /* end of class vector */

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

} /* end of namespace ft */
