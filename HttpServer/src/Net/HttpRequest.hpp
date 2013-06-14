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
#include <utility>

#include "HttpRequestFactory.hpp"

namespace Net
{

class HttpRequest
{
	friend class HttpRequestFactory;

private:

	std::map<std::string, std::string> headers;
	std::map<std::string, std::string> params; //TODO: add params functionality

	HttpRequest() = default;
	HttpRequest(const HttpRequest&) = delete;
	HttpRequest& operator=(const HttpRequest&) = delete;

public:

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
