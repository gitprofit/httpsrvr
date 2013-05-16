//============================================================================
// Name        : HttpServer.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "Logger.hpp"

void testSocket()
{
	struct sockaddr_in stSockAddr;
		int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (-1 == SocketFD)
		{
			perror("can not create socket");
			exit(EXIT_FAILURE);
		}

		memset(&stSockAddr, 0, sizeof(stSockAddr));

		stSockAddr.sin_family = AF_INET;
		stSockAddr.sin_port = htons(1100);
		stSockAddr.sin_addr.s_addr = htonl(INADDR_ANY );

		if (-1
				== bind(SocketFD, (struct sockaddr *) &stSockAddr,
						sizeof(stSockAddr)))
		{
			perror("error bind failed");
			close(SocketFD);
			exit(EXIT_FAILURE);
		}

		if (-1 == listen(SocketFD, 10))
		{
			perror("error listen failed");
			close(SocketFD);
			exit(EXIT_FAILURE);
		}

		//for (;;)
		{
			int ConnectFD = accept(SocketFD, NULL, NULL);

			if (0 > ConnectFD)
			{
				perror("error accept failed");
				close(SocketFD);
				exit(EXIT_FAILURE);
			}

			/* perform read write operations ...
			 read(ConnectFD,buff,size)*/

			char buff[1024];
			int size = read(ConnectFD, buff, sizeof(buff)/sizeof(buff[0]));
			write(STDOUT_FILENO, buff, size);

			if (-1 == shutdown(ConnectFD, SHUT_RDWR))
			{
				perror("can not shutdown socket");
				close(ConnectFD);
				close(SocketFD);
				exit(EXIT_FAILURE);
			}
			close(ConnectFD);
		}

		close(SocketFD);
}

int main()
{
	Logger& logger = Logger::getInstance();

	logger.log("test!");

	return EXIT_SUCCESS;
}
