/*
 * HttpServer.hpp
 *
 *  Created on: Jun 15, 2013
 *      Author: michal
 */

#ifndef HTTPSERVER_HPP_
#define HTTPSERVER_HPP_

#include <memory>
#include <cstdlib>

#include "Util/Logger.hpp"
#include "Util/Config.hpp"
#include "Net/ServerSocket.hpp"
#include "Net/Socket.hpp"

#include "Net/HttpRequest.hpp"
#include "Net/HttpResponse.hpp"
#include "Net/HttpRequestFactory.hpp"
#include "Net/HttpResponseFactory.hpp"


class HttpServer
{

private:

	std::shared_ptr<Net::ServerSocket> serverSocket;

	std::shared_ptr<Net::HttpRequestFactory> requestFactory;
	std::shared_ptr<Net::HttpResponseFactory> responseFactory;

	std::shared_ptr<Util::Config> config;
	std::shared_ptr<Util::Logger> logger;

public:

	HttpServer(std::shared_ptr<Util::Config> config, std::shared_ptr<Util::Logger> logger) :
		config(config), logger(logger)
	{
		requestFactory	= std::make_shared<Net::HttpRequestFactory>();
		responseFactory	= std::make_shared<Net::HttpResponseFactory>();
		serverSocket	= std::make_shared<Net::ServerSocket>(1100);
	}

	void run()
	{
		logger->log("HttpServer start!");
		logger->log("Root dir: " + (*config)["wwwroot"]);

		try
		{
			auto socket = serverSocket->accept();

			std::cout << "got connection!\n";

			auto req = socket->read(requestFactory);

			std::cout << (*req)["Method"] << "\n" << (*req)["URI"] << "\n" << (*req)["User-Agent"] << "\n";

			auto rsp = std::make_shared<Net::HttpResponse>();

			socket->write(rsp);

			std::cout << "connection closed!\n";
			socket->close();
			serverSocket->close();
		}
		catch (Net::NetException& ex)
		{
			std::cout << ex.what() << "\n";
		}
	}
};

#endif /* HTTPSERVER_HPP_ */
