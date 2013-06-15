/*
 * HttpResponseFactory.hpp
 *
 *  Created on: Jun 15, 2013
 *      Author: michal
 */

#ifndef HTTPRESPONSEFACTORY_HPP_
#define HTTPRESPONSEFACTORY_HPP_

#include <cstdlib>

#include "HttpResponse.hpp"

namespace Net
{

class HttpResponseFactory
{

public:

	std::shared_ptr<HttpResponse> create(int statusCode, std::string& content)
	{
		auto response = std::shared_ptr<HttpResponse>(new HttpResponse());
		response->statusCode = statusCode;
		response->content = content;
		response->contentType = "text/html; charset=UTF-8";

		return response;
	}
};

}

#endif /* HTTPRESPONSEFACTORY_HPP_ */
