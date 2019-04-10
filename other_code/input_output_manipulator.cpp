#include <sstream>
#include <locale>
#include <iostream>
#include <iomanip>

int main()
{
	{
		std::cout << "////////////////////////////////////////////////////////////////////////////////" << std::endl;

		// boolalpha 输出
		std::cout << std::boolalpha
			<< "boolalpha true: " << true << '\n'
			<< "boolalpha false: " << false << '\n';
		std::cout << std::noboolalpha
			<< "noboolalpha true: " << true << '\n'
			<< "noboolalpha false: " << false << '\n';
		// boolalpha 分析
		bool b1, b2;
		std::istringstream is("true false");
		is >> std::boolalpha >> b1 >> b2;
		std::cout << '\"' << is.str() << "\" parsed as " << b1 << ' ' << b2 << '\n';

		std::cout << "////////////////////////////////////////////////////////////////////////////////" << std::endl;
	}
	
	{
		std::cout << "////////////////////////////////////////////////////////////////////////////////" << std::endl;

		// showbase 影响八进制和十六进制的输出
		std::cout << std::hex
			<< "showbase: " << std::showbase << 42 << '\n'
			<< "noshowbase: " << std::noshowbase << 42 << '\n';

		// 及货币值的输入和输出
		std::locale::global(std::locale("en_US.utf8"));
		long double val = 0;
		std::istringstream is("3.14");
		is >> std::showbase >> std::get_money(val);
		std::cout << "With showbase, parsing 3.14 as money gives " << val << '\n';
		is.seekg(0);
		is >> std::noshowbase >> std::get_money(val);
		std::cout << "Without showbase, parsing 3.14 as money gives " << val << '\n';

		std::cout << "////////////////////////////////////////////////////////////////////////////////" << std::endl;
	}
	

	system("pause");
	return 0;
}