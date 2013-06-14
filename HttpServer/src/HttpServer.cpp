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
#include "Net/ServerSocket.hpp"
#include "Net/Socket.hpp"

int main()
{
	//Logger& logger = Logger::getInstance();

	try
	{
		Net::ServerSocket serverSocket = Net::ServerSocket(1100);
		Net::Socket socket = serverSocket.accept();

		std::cout << "got connection!\n";

		Net::HttpRequest req = socket.read();

		Net::HttpResponse rsp;

		socket.write(rsp);

		std::cout << "connection closed!\n";
		socket.close();
		serverSocket.close();
	} catch (Net::NetException& ex)
	{
		std::cout << ex.what() << "\n";
	}

	return EXIT_SUCCESS;
}
