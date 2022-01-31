#pragma once
#include <memory>
#include <iterator>
#include <cassert>

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

		typedef std::random_access_iterator_tag		iterator;
		// TODO: add const_iterator?
		typedef std::iterator_traits<iterator>::difference_type	difference_type; // TODO: to check if this is correct

		typedef std::size_t							size_type;
	
	/**** key private member ****/
	private:
		allocator_type	allocator;
		pointer			data;
		size_type		size;
		size_type		capacity;
	
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
size(0),
capacity(0) {}

/* fill constructor */
template< class T, class Alloc >
vector<T, Alloc>::vector(size_type n, const value_type& val, const allocator_type& alloc):
allocator(alloc),
data(NULL),
size(n),
capacity(n) {
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
/**					capacity				**/ 
/*********************************************/
template< class T, class Alloc>
vector<T, Alloc>::size_type	vector<T, Alloc>::size() const{
	return size;
}

template< class T, class Alloc>
vector<T, Alloc>::size_type	vector<T, Alloc>::max_size() const{
	return allocator.max_size();
}

template< class T, class Alloc>
void	vector<T, Alloc>::resize(size_type n, value_type val = value_type()){
	// TODO
}

template< class T, class Alloc>
vector<T, Alloc>::size_type	vector<T, Alloc>::capacity() const{
	return capacity;
}

template< class T, class Alloc>
bool	vector<T, Alloc>::empty() const{
	return size == 0;
}

template< class T, class Alloc>
void	vector<T, Alloc>::reserve(size_type n){
	if (n > capacity)
	{
		new_data = allocator.allocate(n);
		// TODO: assign
		deallocateData();
		data = new_data;
		capacity = n;
	}
}


/*********************************************/ 
/**					modifiers				**/ 
/*********************************************/
template< class T, class Alloc >
void	vector<T, Alloc>::clear(){
	size_type	n = size;
	for (size_type i = 0; i < n; ++i) {
		destroyElement(i);
	}
	assert(size == 0);
}


/*********************************************/ 
/**			private member function			**/ 
/*********************************************/
template< class T, class Alloc >
void	vector<T, Alloc>::destroyElement(size_type index) {
	assert(index < size);
	allocator.destroy(data + index);
	size--;
}

template< class T, class Alloc >
void	vector<T, Alloc>::deallocateData() {
	clear();
	allocator.deallocate(data, capacity);
	data = NULL;
}


} /* end of namespace ft */
