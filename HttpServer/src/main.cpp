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
	std::string configFile = "/home/michal/Documents/HttpServer/server.config";
	std::shared_ptr<Util::Config> config(new Util::Config(configFile));

	std::shared_ptr<Util::Logger> logger(new Util::Logger(std::cout));

	HttpServer server(config, logger);
	server.run();

	return EXIT_SUCCESS;
}
