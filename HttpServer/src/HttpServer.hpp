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

#include "Net/HttpMethod.hpp"
#include "Net/HttpStatusCode.hpp"
#include "Net/HttpContentType.hpp"

#include "Util/Enum.hpp"

#include "File/FileManager.hpp"
#include "File/File.hpp"

#include "RequestHandler.hpp"


class HttpServer
{

private:

	std::shared_ptr<Net::ServerSocket> serverSocket;

	std::shared_ptr<Net::HttpRequestFactory> requestFactory;
	std::shared_ptr<Net::HttpResponseFactory> responseFactory;

	std::shared_ptr<File::FileManager> fileManager;

	std::shared_ptr<Util::Config> config;
	std::shared_ptr<Util::Logger> logger;

public:

	HttpServer(std::shared_ptr<Util::Config> config, std::shared_ptr<Util::Logger> logger) :
		config(config), logger(logger)
	{
		serverSocket	= std::make_shared<Net::ServerSocket>(8080);
		requestFactory	= std::make_shared<Net::HttpRequestFactory>();
		responseFactory	= std::make_shared<Net::HttpResponseFactory>();
		fileManager		= std::make_shared<File::FileManager>((*config)["wwwroot"]);
	}

	void run()
	{
		logger->log("HttpServer start!");
		logger->log("Root dir: " + (*config)["wwwroot"]);

		for(;;)
		{
			try
			{
				auto socket = serverSocket->accept();

				auto requestHandler = new RequestHandler(
						socket,
						requestFactory, responseFactory,
						fileManager,
						config, logger);

				requestHandler->start();
			}
			catch(Util::Exception& ex)
			{
				logger->log(ex.what());
			}
		}

		serverSocket->close();
	}
};

#endif /* HTTPSERVER_HPP_ */
