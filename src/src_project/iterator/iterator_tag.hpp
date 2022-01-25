#pragma once

namespace ft {

/*
**	These are empty types, used to distinguish different iterators.
*/
struct input_iterator_tag{};
struct output_iterator_tag{};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

} /* end of namespace ft */
