//============================================================================
// Name        : HttpServer.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>

#include "Logger.hpp"
#include "Net/Socket.hpp"
#include "Net/Connection.hpp"

int main()
{
	//Logger& logger = Logger::getInstance();

	try
	{
		Net::Socket sock = Net::Socket(1100);
		Net::Connection conn = sock.accept();

		std::cout << "got connection!\n";

		Net::HttpRequest req = conn.read();

		std::cout << "connection closed!\n";
		conn.close();
		sock.close();
	} catch (Net::NetException& ex)
	{
		std::cout << ex.what() << "\n";
	}

	return EXIT_SUCCESS;
}
