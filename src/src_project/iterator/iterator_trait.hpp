#pragma once

namespace ft {

template<class Iterator>
struct iterator_traits {
  typedef typename Iterator::difference_type 	difference_type;
  typedef typename Iterator::value_type 		value_type;
  typedef typename Iterator::pointer 			pointer;
  typedef typename Iterator::reference 			reference;
  typedef typename Iterator::iterator_category	iterator_category;
};

template<class T>
struct iterator_traits<T*> {
  typedef typename T::difference_type 	difference_type;
  typedef typename T::value_type 		value_type;
  typedef typename T::pointer 			pointer;
  typedef typename T::reference 			reference;
  typedef typename T::iterator_category	iterator_category;
};

template<class T>
struct iterator_traits<T&> {
  typedef typename T::difference_type 	difference_type;
  typedef typename T::value_type 		value_type;
  typedef typename T::pointer 			pointer;
  typedef typename T::reference 			reference;
  typedef typename T::iterator_category	iterator_category;
};

} /* end of namespace ft */
