/*
 * main.cpp
 *
 *  Created on: Jun 15, 2013
 *      Author: michal
 */

#include <memory>

#include "HttpServer.hpp"


int main()
{
	std::shared_ptr<Util::Logger> logger(new Util::Logger(std::cout));

	std::string configFile = "/home/michal/Documents/HttpServer/server.config";
	std::shared_ptr<Util::Config> config;

	try
	{
		config = std::make_shared<Util::Config>(configFile);
	}
	catch(Util::Exception& ex)
	{
		logger->log(ex.what());
	}



	HttpServer server(config, logger);
	server.run();

	return EXIT_SUCCESS;
}
