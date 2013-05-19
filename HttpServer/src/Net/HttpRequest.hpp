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

#include "HttpMethod.hpp"

namespace Net
{

class HttpRequest
{
	friend class Connection;

private:

	HttpMethod method;
	std::string URI;
	std::map<std::string, std::string> headers;

	HttpRequest(std::list<std::string>& rawRequest)
	{
		method = HttpMethod::GET;
		URI = "/";

		rawRequest.pop_front();
		rawRequest.pop_front();

		for(auto& line : rawRequest)
		{
			auto start = line.find(": ");

			auto name = line.substr(0, start);
			auto value = line.substr(start + 2);

			headers[name] = value;
		}
	}

public:

	HttpMethod getMethod()
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

		if(it == headers.end())
			throw NetException("HttpRequest::operator[]", "header '" + headerName + "' not found");

		return it->second;
	}
};

}

#endif /* HTTPREQUEST_HPP_ */
