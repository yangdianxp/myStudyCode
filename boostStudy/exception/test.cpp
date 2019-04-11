
#if 0

#include <boost/exception/all.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/exception/errinfo_file_open_mode.hpp>
#include <boost/exception/errinfo_file_handle.hpp>
#include <boost/exception/errinfo_file_name.hpp>
#include <boost/exception/errinfo_api_function.hpp>
#include <boost/exception/errinfo_errno.hpp>
#include <stdio.h>
#include <errno.h>
#include <string>

struct file_read_error : virtual boost::exception { };

void
file_read(FILE * f, void * buffer, size_t size)
{
	if (size != fread(buffer, 1, size, f))
		throw file_read_error() << boost::errinfo_errno(errno);
}

typedef boost::tuple<boost::errinfo_api_function, boost::errinfo_errno> clib_failure;

struct file_open_error : virtual boost::exception { };

boost::shared_ptr<FILE>
file_open(char const * name, char const * mode)
{
	if (FILE * f = fopen(name, mode))
		return boost::shared_ptr<FILE>(f, fclose);
	else
		throw file_open_error() << 
		boost::errinfo_file_name(name) << 
		clib_failure("fopen", errno);
}

int main()
{
	std::string file_name = "temp.txt";
	try
	{
		boost::shared_ptr<FILE> f = file_open(file_name.c_str(), "rb");
		assert(f);

		char buf[1024];
		file_read(f.get(), buf, sizeof(buf));
	}
	catch (
		boost::exception & e)
	{
		e << boost::errinfo_file_name(file_name);
		throw;
	}

	system("pause");
	return 0;
}

BOOST_THROW_EXCEPTION
fopen_error

#endif

#if 1

//Àý³Ì
#include <boost/exception/all.hpp>
#include <iostream>

typedef boost::error_info<struct tag_my_info, char const *> my_info; //(1)

struct my_error : virtual boost::exception, virtual std::exception { }; //(2)

void f()
{
	my_error e = my_error();
	e << my_info("aaaaaaaaaaaaaaaaaaaaaa");

	BOOST_THROW_EXCEPTION(e); //(3)
}

int main()
{
	try
	{
		f();
	}
	catch (boost::exception& e)
	{
		if (char const ** mi = boost::get_error_info<my_info>(e))
			std::cerr << "My info: " << *mi << std::endl;;
		std::cerr << *(boost::get_error_info<boost::throw_function>(e)) << std::endl;
		std::cerr << *(boost::get_error_info<boost::throw_file>(e)) << std::endl;
		std::cerr << *(boost::get_error_info<boost::throw_line>(e)) << std::endl;
	}

	system("pause");
	return 0;
}
#endif