#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#include <iostream>

int main()
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		std::cout << "create socket error:" << strerror(errno);
	}
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(atoi("23458"));
	int flags = fcntl(sock, F_GETFL, 0);
	fcntl(sock, F_SETFL, flags | O_NONBLOCK);
	int n = 0;
	if ((n = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) == -1)
	{
		if (errno != EINPROGRESS)
		{
			std::cout << "connect error:" << strerror(errno) << std::endl;;
		}
	}
	if (n == 0)
	{
		std::cout << "connect succ immediately" << std::endl;
		return 0;
	}

	std::cout << "connect n:" << n << std::endl;;
	int epfd, nfds;
	struct epoll_event ev, events[5]; //ev用于注册事件，数组用于返回要处理的事件
	epfd = epoll_create(1); //只需要监听一个描述符
	ev.data.fd = sock;
	ev.events = EPOLLIN | EPOLLOUT | EPOLLET; //监听读状态同时设置ET模式
	epoll_ctl(epfd, EPOLL_CTL_ADD, sock, &ev); //注册epoll事件
	for (;;)
	{
		nfds = epoll_wait(epfd, events, 5, -1);
		for (int i = 0; i < nfds; i++)
		{
			
			if (events[i].data.fd == sock &&
				(events[i].events & (EPOLLIN | EPOLLOUT)))
			{
				int error = 0;
				int len = sizeof(error);
				if (getsockopt(sock, SOL_SOCKET, SO_ERROR, &error, (socklen_t *)&len) < 0)
				{
					std::cout << "getsockopt error:" << strerror(errno) << std::endl;
					return -1;
				}
				if (error)
				{
					close(sock);
					errno = error;
					std::cout << "connect fail:" << strerror(errno) << std::endl;
					return -1;
				}

				std::cout << "connect succ!\n" << std::endl;
			}
				
		}
	}

	return 0;
}