/*
 * HttpRequest.hpp
 *
 *  Created on: May 16, 2013
 *      Author: michal
 */

#ifndef HTTPREQUEST_HPP_
#define HTTPREQUEST_HPP_

#include <map>
#include <list>
#include <sstream>

namespace Net
{

class HttpRequest
{
	friend class Connection;

private:

	std::string method;
	std::string URI;
	std::map<std::string, std::string> headers;
	std::map<std::string, std::string> params; //TODO: add params functionality

	HttpRequest(std::list<std::string>& rawRequest)
	{
		std::istringstream iss(rawRequest.front());
		iss >> method;
		iss >> URI;
		headers["Method"] = method;
		headers["URI"] = URI;

		rawRequest.pop_front();

		for (auto& line : rawRequest)
		{
			auto start = line.find(": ");

			auto name = line.substr(0, start);
			auto value = line.substr(start + 2);

			headers[name] = value;
		}
	}


public:

	std::string getMethod()
	{
		return method;
	}

	std::string getURI()
	{
		return URI;
	}

	std::string operator[](const std::string& headerName)
	{
		auto it = headers.find(headerName);

		if (it == headers.end())
			throw NetException("HttpRequest::operator[]",
					"header '" + headerName + "' not found");

		return it->second;
	}
};

}

#endif /* HTTPREQUEST_HPP_ */
