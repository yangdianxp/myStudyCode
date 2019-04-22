#include <iostream>

#include <boost/fiber/all.hpp>

using namespace boost::fibers;
using namespace boost::this_fiber;

boost::fibers::fiber f1;

void f() {
	boost::fibers::fiber f2(some_fn);

	f1 = std::move(f2); // f2 moved to f1
}

int main()
{

	system("pause");
	return 0;
}