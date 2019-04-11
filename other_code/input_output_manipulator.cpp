#include <sstream>
#include <locale>
#include <iostream>
#include <iomanip>
#include <chrono>

template<typename Diff>
void log_progress(Diff d)
{
	std::cout << "..("
		<< std::chrono::duration_cast<std::chrono::milliseconds>(d).count()
		<< " ms)..";
}

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

		std::cout << std::dec;

		std::cout << "////////////////////////////////////////////////////////////////////////////////" << std::endl;
	}

	{
		std::cout << "////////////////////////////////////////////////////////////////////////////////" << std::endl;

		std::cout << "1.0 with showpoint: " << std::showpoint << 1.0 << '\n'
			<< "1.0 with noshowpoint: " << std::noshowpoint << 1.0 << '\n';

		std::cout << "////////////////////////////////////////////////////////////////////////////////" << std::endl;
	}

	{
		std::cout << "////////////////////////////////////////////////////////////////////////////////" << std::endl;

		std::cout << "showpos: " << std::showpos << 42 << ' ' << 3.14 << ' ' << 0 << '\n'
			<< "noshowpos: " << std::noshowpos << 42 << ' ' << 3.14 << ' ' << 0 << '\n';

		std::cout << "////////////////////////////////////////////////////////////////////////////////" << std::endl;
	}

	{
		std::cout << "////////////////////////////////////////////////////////////////////////////////" << std::endl;

		char c1, c2, c3;
		std::istringstream("a b c") >> c1 >> c2 >> c3;
		std::cout << "Default  behavior: c1 = " << c1 << " c2 = " << c2 << " c3 = " << c3 << '\n';
		std::istringstream("a b c") >> std::noskipws >> c1 >> c2 >> c3;
		std::cout << "noskipws behavior: c1 = " << c1 << " c2 = " << c2 << " c3 = " << c3 << '\n';

		std::cout << "////////////////////////////////////////////////////////////////////////////////" << std::endl;
	}

	{
		std::cout << "////////////////////////////////////////////////////////////////////////////////" << std::endl;

		std::cout << std::hex << std::showbase
			<< "0x2a with uppercase: " << std::uppercase << 0x2a << '\n'
			<< "0x2a with nouppercase: " << std::nouppercase << 0x2a << '\n'
			<< "1e-10 with uppercase: " << std::uppercase << 1e-10 << '\n'
			<< "1e-10 with nouppercase: " << std::nouppercase << 1e-10 << '\n';

		std::cout << std::dec;
		std::cout << std::noshowbase;

		std::cout << "////////////////////////////////////////////////////////////////////////////////" << std::endl;
	}

	{
		std::cout << "////////////////////////////////////////////////////////////////////////////////" << std::endl;

		//volatile int sink = 0;
		////std::cout << std::unitbuf; // 启用自动冲入
		//std::cout << std::nounitbuf;

		//auto t1 = std::chrono::high_resolution_clock::now();
		//for (int j = 0; j < 5; ++j)
		//{
		//	for (int n = 0; n < 10000; ++n)
		//		for (int m = 0; m < 20000; ++m)
		//			sink += m * n; // 做一些工作
		//	auto now = std::chrono::high_resolution_clock::now();
		//	log_progress(now - t1);
		//}
		//std::cout << '\n';

		std::cout << "////////////////////////////////////////////////////////////////////////////////" << std::endl;
	}

	{
		std::cout << "////////////////////////////////////////////////////////////////////////////////" << std::endl;

		std::cout.imbue(std::locale("en_US.utf8"));
		std::cout << "Left fill:\n" << std::left << std::setfill('*')
			<< std::setw(12) << -1.23 << '\n'
			<< std::setw(12) << std::hex << std::showbase << 42 << '\n'
			<< std::setw(12) << std::put_money(123, true) << "\n\n";

		std::cout << "Internal fill:\n" << std::internal
			<< std::setw(12) << -1.23 << '\n'
			<< std::setw(12) << 42 << '\n'
			<< std::setw(12) << std::put_money(123, true) << "\n\n";

		std::cout << "Right fill:\n" << std::right
			<< std::setw(12) << -1.23 << '\n'
			<< std::setw(12) << 42 << '\n'
			<< std::setw(12) << std::put_money(123, true) << '\n';

		std::cout << "////////////////////////////////////////////////////////////////////////////////" << std::endl;
	}

	{
		std::cout << "////////////////////////////////////////////////////////////////////////////////" << std::endl;

		std::cout << "The number 42 in octal:   " << std::oct << 42 << '\n'
			<< "The number 42 in decimal: " << std::dec << 42 << '\n'
			<< "The number 42 in hex:     " << std::hex << 42 << '\n';
		int n;
		std::istringstream("2A") >> std::hex >> n;
		std::cout << std::dec << "Parsing \"2A\" as hex gives " << n << '\n';
		// 输出基底是持久的，直至更改
		std::cout << std::hex << "42 as hex gives " << 42
			<< " and 21 as hex gives " << 21 << '\n';

		std::cout << "////////////////////////////////////////////////////////////////////////////////" << std::endl;
	}

	{
		std::cout << "////////////////////////////////////////////////////////////////////////////////" << std::endl;

		std::cout << "The number 0.01 in fixed:      " << std::fixed << 0.01 << '\n'
			<< "The number 0.01 in scientific: " << std::scientific << 0.01 << '\n'
			<< "The number 0.01 in hexfloat:   " << std::hexfloat << 0.01 << '\n'
			<< "The number 0.01 in default:    " << std::defaultfloat << 0.01 << '\n';
		double f;
		std::istringstream("0x1P-1022") >> std::hexfloat >> f;
		std::cout << "Parsing 0x1P-1022 as hex gives " << f << '\n';

		std::cout << "////////////////////////////////////////////////////////////////////////////////" << std::endl;
	}

	{
		std::cout << "////////////////////////////////////////////////////////////////////////////////" << std::endl;

		std::istringstream s("     this is a test     ");
		std::string line;
		std::getline(s >> std::ws, line);
		std::cout << "ws + getline returns: \"" << line << "\"\n";

		//std::stringstream ss("  1  ");
		//std::string num;
		//ss /*>> std::ws*/ >> num;
		//std::cout << "num:" << num << "\n";

		std::cout << "////////////////////////////////////////////////////////////////////////////////" << std::endl;
	}
	

	system("pause");
	return 0;
}