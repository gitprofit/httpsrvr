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

	//std::string magicData = "GET / HTTP/1.1\r\nHost: atasoyweb.net\r\nUser-Agent: Mozilla/5.0 (Windows NT 6.1; rv:14.0) Gecko/20100101 Firefox/14.0.1\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: tr-tr,tr;q=0.8,en-us;q=0.5,en;q=0.3\r\nAccept-Encoding: gzip, deflate\r\nConnection: keep-alive\r\n\r\n";
	/*std::istringstream iss(magicData);
	std::string line;
	while(std::getline(iss, line))
	{
		line.pop_back();
		std::cout << "mam: " << line << "\nend\n";
	}*/

	//return 0;

	Logger& logger = Logger::getInstance();

	try
	{
		Net::Socket sock = Net::Socket(1100);
		Net::Connection conn = sock.accept();

		std::cout << "got connection!\n";

		Net::HttpRequest req = conn.read();

		std::cout << req["User-Agent"] << "\n";
		std::cout << "here!";
		conn.close();
		sock.close();
	}
	catch(Net::NetException& ex)
	{
		std::cout << ex.what() << "\n";
	}

	return EXIT_SUCCESS;
}
