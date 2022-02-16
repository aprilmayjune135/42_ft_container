#include "test.hpp"

#ifdef STANDARD
	#include <vector>
#else
	#include "../container/vector.hpp"
#endif

#include "Dummy.hpp"
#include "../utility/namespace.hpp"
#include "../utility/Print.hpp"
#include "../utility/print_container.hpp"
#include "../utility/log_formatting.hpp"


namespace vector {
typedef	Dummy<int>					t_dummy;
typedef ft::vector<int> 			t_container_int;
typedef ft::vector<std::string>		t_container_str;
typedef ft::vector<t_dummy>			t_container_dummy;

void	testConstructor() {
	logTitleSection("empty constructor");
	t_container_int 	v_empty_int;
	printVector(v_empty_int);
	t_container_str 	v_empty_str;
	printVector(v_empty_str);
	t_container_dummy	v_empty_dummy;
	printVector(v_empty_dummy);
	
	logTitleSection("fill constructor");
	t_container_int 	v_fill_int(100, 5);
	printVector(v_fill_int);
	t_container_str 	v_fill_str(50, "hello!");
	printVector(v_fill_str);
	t_container_dummy	v_fill_dummy(20, t_dummy(42));
	printVector(v_fill_dummy);

	logTitleSection("range constructor");
	t_container_int 	v_range_int(v_fill_int.begin(), v_fill_int.end());
	printVector(v_range_int);
	t_container_str 	v_range_str(v_fill_str.begin(), v_fill_str.end());
	printVector(v_range_str);
	t_container_dummy	v_range_dummy(v_fill_dummy.begin(), v_fill_dummy.end());
	printVector(v_range_dummy);

	logTitleSection("copy constructor");
	t_container_int 	v_copy_int(v_range_int);
	printVector(v_copy_int);
	t_container_str 	v_copy_str(v_range_str);
	printVector(v_copy_str);
	t_container_dummy	v_copy_dummy(v_range_dummy);
	printVector(v_copy_dummy);

	logTitleSection("operator= (new)");
	t_container_int v_equal_int = v_fill_int;
	printVector(v_equal_int);
	t_container_str v_equal_str = v_fill_str;
	printVector(v_equal_str);
	t_container_dummy v_equal_dummy = v_fill_dummy;
	printVector(v_equal_dummy);

	logTitleSection("operator= (existing)");
	v_empty_int = v_fill_int;
	printVector(v_empty_int);
	v_empty_str = v_fill_str;
	printVector(v_empty_str);
	v_empty_dummy = v_fill_dummy;
	printVector(v_empty_dummy);

}

void	testIterator() {
}

void	testCapacity() {
}

void	testElementAccess() {
}

void	testModifiers() {
}

void	testAllocator() {
}

void	testOperator() {
}

} /* end of namespace vector */
