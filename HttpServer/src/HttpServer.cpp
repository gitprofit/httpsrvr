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
		Net::Socket socket = Net::Socket(1100);
		Net::Connection connection = socket.accept();

		std::cout << "got connection!\n";

		Net::HttpRequest req = connection.read();

		Net::HttpResponse rsp;

		connection.write(rsp);

		std::cout << "connection closed!\n";
		connection.close();
		socket.close();
	} catch (Net::NetException& ex)
	{
		std::cout << ex.what() << "\n";
	}

	return EXIT_SUCCESS;
}
