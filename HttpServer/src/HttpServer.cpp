//============================================================================
// Name        : HttpServer.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>

#include "Util/Logger.hpp"
#include "Util/Config.hpp"
#include "Net/ServerSocket.hpp"
#include "Net/Socket.hpp"

int main()
{
	//Util::Logger& logger = Util::Logger::get();

	Util::Config& config = Util::Config::get();
	config.reload("/home/michal/Documents/HttpServer/server.config");
	std::cout << config["wwwroot"] << "\n";

	HttpRequestFactory requestFactory;


	try
	{
		Net::ServerSocket serverSocket = Net::ServerSocket(1100);
		Net::Socket socket = serverSocket.accept();

		std::cout << "got connection!\n";

		Net::HttpRequest req = socket.read(requestFactory);

		std::cout << req["Method"] << "\n" << req["URI"] << "\n" <<req["User-Agent"] << "\n";

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
