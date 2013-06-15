/*
 * HttpServer.hpp
 *
 *  Created on: Jun 15, 2013
 *      Author: michal
 */

#ifndef HTTPSERVER_HPP_
#define HTTPSERVER_HPP_

#include <iostream>
#include <cstdlib>

#include "Util/Logger.hpp"
#include "Util/Config.hpp"
#include "Net/ServerSocket.hpp"
#include "Net/Socket.hpp"

#include "Net/HttpRequest.hpp"
#include "Net/HttpResponse.hpp"
#include "Net/HttpRequestFactory.hpp"

class HttpServer
{
public:

	HttpServer()
	{
		//
	}

	void run()
	{

		Util::Config& config = Util::Config::get();
		config.reload("/home/michal/Documents/HttpServer/server.config");
		std::cout << config["wwwroot"] << "\n";




		try
		{
			Net::HttpRequestFactory requestFactory;

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
	}
};

#endif /* HTTPSERVER_HPP_ */
