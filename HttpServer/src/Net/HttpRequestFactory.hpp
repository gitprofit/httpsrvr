/*
 * HttpRequestFactory.hpp
 *
 *  Created on: Jun 15, 2013
 *      Author: michal
 */

#ifndef HTTPREQUESTFACTORY_HPP_
#define HTTPREQUESTFACTORY_HPP_

#include <memory>
#include <cstdlib>

#include "SocketIstream.hpp"
#include "HttpRequest.hpp"
#include "HttpMethod.hpp"

namespace Net
{

class HttpRequestFactory
{

public:

	std::shared_ptr<HttpRequest> create(int rawUglySocketFD)
	{
		// ugly make_shared needs public constructor
		// otherwise g++ crashes
		//auto request = std::make_shared<HttpRequest>();

		auto request = std::shared_ptr<HttpRequest>(new HttpRequest());

		std::string line;
		SocketIstream socketStream(rawUglySocketFD);

		std::getline(socketStream, line);

		std::istringstream iss(line);
		iss >> request->headers["Method"];
		iss >> request->headers["URI"];

		request->method = HttpMethod::fromString(request->headers["Method"]);

		if(request->method == HttpMethod::GET)
		{
			// remove GET vars

			auto pos = request->headers["URI"].find("?");
			if(pos != std::string::npos)
				request->headers["URI"] = request->headers["URI"].substr(0, pos);
		}

		while(std::getline(socketStream, line))
		{
			auto start = line.find(": ");
			auto name = line.substr(0, start);
			auto value = line.substr(start + 2);
			request->headers[name] = value;
		}

		try
		{
			auto contentLength = (*request)["Content-Length"]; // throws if not found
			std::string rawContent;

			int size = ::atoi(contentLength.c_str());
			rawContent.resize(size);
			::read(rawUglySocketFD, &rawContent[0], size);
		}
		catch(NetException& ex) { }

		return request;
	}
};

}

#endif /* HTTPREQUESTFACTORY_HPP_ */
