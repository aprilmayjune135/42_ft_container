#pragma once

namespace ft {

/*
**	Iterator tages.
**	These are empty types, used to distinguish different iterators.
*/

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag  : public bidirectional_iterator_tag {};

/*
**	Iterator traits.
*/

template<class T>
struct iterator_traits {
  typedef typename T::difference_type 	difference_type;
  typedef typename T::value_type 		    value_type;
  typedef typename T::pointer 			    pointer;
  typedef typename T::reference 			  reference;
  typedef typename T::iterator_category	iterator_category;
};

template<class T>
struct iterator_traits<T*> {
  typedef typename T::difference_type 	difference_type;
  typedef typename T::value_type 		    value_type;
  typedef typename T::pointer 			    pointer;
  typedef typename T::reference 			  reference;
  typedef typename T::iterator_category	iterator_category;
};

template<class T>
struct iterator_traits<T&> {
  typedef typename T::difference_type 	difference_type;
  typedef typename T::value_type 		    value_type;
  typedef typename T::pointer 			    pointer;
  typedef typename T::reference 			  reference;
  typedef typename T::iterator_category	iterator_category;
};

} /* end of namespace ft */
