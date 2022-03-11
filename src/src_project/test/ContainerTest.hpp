#pragma once
#include <string>
#define EXTREME_MAP 100000
#define EXTREME_SET 100000

class ContainerTest {
	public:
		ContainerTest(const std::string& type);
		virtual ~ContainerTest() {};
		
		void	test(int category);
		virtual void	testConstructor() {};
		virtual void	testIterator() {};
		virtual void	testCapacity() {};
		virtual void	testElementAccess() {};
		virtual void	testModifiers() {};
		virtual void	testAllocator() {};
		virtual void	testOperator() {};
	
	protected:
		std::string container_type;
		ContainerTest() {};

};

template <class V>
class Source {
	public:
		Source(std::size_t n);
		~Source() {};
		std::string 	type;
		V				data;
	private:
		Source() {};

};
