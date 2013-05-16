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

/*
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
*/

#include "Logger.hpp"
#include "Net/HttpRequest.hpp"
#include "Net/Socket.hpp"


int main()
{
	Logger& logger = Logger::getInstance();

	try
	{
		Net::Socket sock = Net::Socket(1100);
		std::string req = sock.accept();
		sock.close();

		std::cout << req;
	}
	catch(Net::NetException& ex)
	{
		std::cout << ex.what() << "\n";
	}

	return EXIT_SUCCESS;
}
