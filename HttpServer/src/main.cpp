/*
 * main.cpp
 *
 *  Created on: Jun 15, 2013
 *      Author: michal
 */

#include "HttpServer.hpp"

int main()
{
	//Util::Logger& logger = Util::Logger::get();
	HttpServer server;
	server.run();
	return EXIT_SUCCESS;
}
