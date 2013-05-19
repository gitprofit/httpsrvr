/*
 * HttpRequest.hpp
 *
 *  Created on: May 16, 2013
 *      Author: michal
 */

#ifndef HTTPREQUEST_HPP_
#define HTTPREQUEST_HPP_

#include "HttpMethod.hpp"
#include <map>

namespace Net
{

class HttpRequest
{
	friend class Connection;

private:

	HttpMethod method;
	std::string URI;
	std::map<std::string, std::string> headers;

	void addHeader(std::string name, std::string value)
	{
		headers[name] = value;
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

	std::string operator[](std::string headerName)
	{
		auto it = headers.find(headerName);

		if(it == headers.end())
			throw NetException("HttpRequest::operator[]", "header '" + headerName + "' not found");

		return it->second;
	}
};

}

#endif /* HTTPREQUEST_HPP_ */
