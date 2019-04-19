#include <iostream>
#include <string>
#include <functional>
#include <thread>
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

using boost::asio::ip::tcp;

void recv_func(tcp::iostream& stream, boost::asio::steady_timer& timer, const boost::system::error_code& ec)
{
	std::cout << ec.value() << ec.message() << std::endl;
	std::cout << "aaaaaaaaaaaaaaaaaaa" << std::endl;
	timer.expires_from_now(std::chrono::seconds(3));
	timer.async_wait(std::bind(recv_func, std::ref(stream), std::ref(timer), std::placeholders::_1));
}

void send_func(tcp::iostream& stream, boost::asio::steady_timer& timer, const boost::system::error_code& ec)
{
	std::cout << ec.value() << ec.message() << std::endl;
	std::string str("hahahahaha");
	stream << str << std::endl;
	timer.expires_from_now(std::chrono::seconds(2));
	timer.async_wait(std::bind(send_func, std::ref(stream), std::ref(timer), std::placeholders::_1));
}

int main()
{
	boost::asio::io_context io_context;
	tcp::endpoint ep(tcp::v4(), 6688);
	tcp::acceptor acceptor(io_context, ep);

	tcp::iostream tcp_stream;
	acceptor.accept(*tcp_stream.rdbuf());

	boost::asio::steady_timer timer(io_context);
	timer.expires_from_now(std::chrono::seconds(3));
	boost::asio::steady_timer timer1(io_context);
	timer1.expires_from_now(std::chrono::seconds(2));
	timer.async_wait(std::bind(recv_func, std::ref(tcp_stream), std::ref(timer), std::placeholders::_1));
	timer1.async_wait(std::bind(send_func, std::ref(tcp_stream), std::ref(timer1), std::placeholders::_1));

	io_context.run();

	system("pause");
}

#if 0
tcp::iostream tcp_stream("192.168.0.174", "8080");
while (true)
{
	tcp_stream << "hahaha" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
}

tcp_stream.close();


boost::asio::io_context io_context;
tcp::resolver r(io_context);
tcp::resolver::query q("www.baidu.com", "https");
auto iter = r.resolve(q);
decltype(iter) end;
for (; iter != end; ++iter)
{
	auto addr = iter->endpoint().address();
	auto port = iter->endpoint().port();
	std::cout << addr.to_string() << std::endl;
	std::cout << port << std::endl;
}



//
// echo_server.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/write.hpp>
#include <iostream>
#include <memory>

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session>
{
public:
	explicit session(boost::asio::io_context& io_context, tcp::socket socket)
		: socket_(std::move(socket)),
		timer_(io_context),
		strand_(io_context.get_executor())
	{
	}

	void go()
	{
		auto self(shared_from_this());
		boost::asio::spawn(strand_,
			[this, self](boost::asio::yield_context yield)
		{
			try
			{
				char data[128];
				for (;;)
				{
					timer_.expires_from_now(std::chrono::seconds(10));
					std::size_t n = socket_.async_read_some(boost::asio::buffer(data), yield);
					boost::asio::async_write(socket_, boost::asio::buffer(data, n), yield);
				}
			}
			catch (std::exception& e)
			{
				socket_.close();
				timer_.cancel();
			}
		});

		boost::asio::spawn(strand_,
			[this, self](boost::asio::yield_context yield)
		{
			while (socket_.is_open())
			{
				boost::system::error_code ignored_ec;
				timer_.async_wait(yield[ignored_ec]);
				if (timer_.expires_from_now() <= std::chrono::seconds(0))
					socket_.close();
			}
		});
	}

private:
	tcp::socket socket_;
	boost::asio::steady_timer timer_;
	boost::asio::strand<boost::asio::io_context::executor_type> strand_;
};

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: echo_server <port>\n";
			return 1;
		}

		boost::asio::io_context io_context;

		auto func = [&](boost::asio::yield_context yield)
		{
			std::cout << "test test" << std::endl;
		};

		boost::asio::spawn(io_context, 
			[&](boost::asio::yield_context yield)
		{
			std::cout << "test test" << std::endl;
		});

		//boost::asio::post(io_context, [&]()
		//{
		//	//std::cout << ec.message() << std::endl;
		//	std::cout << "wa wa" << std::endl;
		//});

		io_context.post([&]()
		{
			//std::cout << ec.message() << std::endl;
			std::cout << "wa wa" << std::endl;
		});

		boost::asio::spawn(io_context,
			[&](boost::asio::yield_context yield)
		{
			tcp::acceptor acceptor(io_context,
				tcp::endpoint(tcp::v4(), std::atoi(argv[1])));

			for (;;)
			{
				boost::system::error_code ec;
				tcp::socket socket(io_context);
				acceptor.async_accept(socket, yield[ec]);
				if (!ec)
				{
					std::make_shared<session>(io_context, std::move(socket))->go();
				}
			}
		});

		io_context.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}

#endif



//#include <boost/asio/yield.hpp>
//#include <boost/asio/coroutine.hpp>
//#include <iostream>
//
//boost::asio::coroutine c;
//
//void foo(int i)
//{
//	reenter(c)
//	{
//		yield std::cout << "foo1 " << i << std::endl;
//		fork foo(100);
//		yield std::cout << "foo2 " << i + 1 << std::endl;
//	}
//}
//int main()
//{
//	foo(1);
//	foo(2);
//	foo(3);
//	system("pause");
//	return 0;
//}