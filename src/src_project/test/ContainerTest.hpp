#pragma once
#include <string>

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
