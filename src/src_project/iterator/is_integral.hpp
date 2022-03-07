#pragma once

namespace ft {

template <typename T, typename = void>
struct is_integral { const static bool	value = false; };

template <>
struct is_integral<bool> { const static bool	value = true; };

template <>
struct is_integral<char> { const static bool	value = true; };

template <>
struct is_integral<char16_t> { const static bool	value = true; };

template <>
struct is_integral<char32_t> { const static bool	value = true; };

template <>
struct is_integral<wchar_t> { const static bool	value = true; };

template <>
struct is_integral<signed char> { const static bool	value = true; };

template <>
struct is_integral<short int> { const static bool	value = true; };

template <>
struct is_integral<int> { const static bool	value = true; };

template <>
struct is_integral<long int> { const static bool	value = true; };

template <>
struct is_integral<unsigned char> { const static bool	value = true; };

template <>
struct is_integral<unsigned short int> { const static bool	value = true; };

template <>
struct is_integral<unsigned int> { const static bool	value = true; };

template <>
struct is_integral<unsigned long int> { const static bool	value = true; };

} /* end of namespace ft */
