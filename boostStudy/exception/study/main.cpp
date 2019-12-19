#include <iostream>
#include <string>
#include <boost/exception/all.hpp>

#define EXPINFO(msg) (std::string(__FILE__) + ":" + std::to_string(__LINE__) + " " + __FUNCTION__ + " " + (msg))

typedef boost::error_info<struct tag_err_info, std::string> err_str;

struct my_exception : virtual boost::exception, virtual std::exception {};

void f()
{
	throw my_exception() << err_str(EXPINFO("aaaaaaaaa"));
}

int main()
{
	try {
		try {
			f();
		}
		catch (my_exception& e)
		{
			auto a = boost::get_error_info<err_str>(e);
			std::cout << *a << std::endl;
			e << err_str(*a + "<=>" + EXPINFO("bbbbbbbbbbb"));
			throw;
		}
	}
	catch (my_exception& e)
	{
		auto a = boost::get_error_info<err_str>(e);
		std::cout << e.what() << " " << *a << std::endl;
	}
	
	return 0;

}