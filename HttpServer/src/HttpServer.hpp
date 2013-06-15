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

		//logger->log(Net::HttpStatusCode::OK->toString());

		for(auto code : Net::HttpContentType::values)
		{
			//logger->log(code->toString());
		}
/*
		for(auto code : Net::HttpMethod2::values)
			logger->log(code->toString());

		logger->log("first: " + Net::HttpMethod2::fromString("GET")->toString());

		for(auto code : Net::HttpStatusCode2::values)
			logger->log(code->toString());

		logger->log("second: " + Net::HttpStatusCode2::fromString("404 Not Found")->toString());

		for(auto code : Net::HttpMethod2::values)
			logger->log(code->toString());

		logger->log("third: " + Net::HttpMethod2::fromString("GET")->toString());
*/

		for(auto code : Net::HttpMethod::values)
			logger->log(code->toString());

		logger->log("third: " + Net::HttpMethod::fromString("GET")->toString());

		return;

		try
		{
			auto socket = serverSocket->accept();

			std::cout << "got connection!\n";

			auto req = socket->read(requestFactory);

			std::cout << (*req)["Method"] << "\n" << (*req)["URI"] << "\n" << (*req)["User-Agent"] << "\n";

			std::string s = "";
			auto rsp = responseFactory->create(404, s);

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
