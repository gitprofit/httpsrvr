/*
 * HttpResponseFactory.hpp
 *
 *  Created on: Jun 15, 2013
 *      Author: michal
 */

#ifndef HTTPRESPONSEFACTORY_HPP_
#define HTTPRESPONSEFACTORY_HPP_

#include <cstdlib>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "HttpResponse.hpp"
#include "../File/File.hpp"

namespace Net
{

class HttpResponseFactory
{

public:

	std::shared_ptr<HttpResponse> fromString(std::shared_ptr<HttpStatusCode> statusCode,
			std::shared_ptr<HttpContentType> contentType, std::shared_ptr<std::string> rawContent)
	{
		auto response = std::shared_ptr<HttpResponse>(new HttpResponse());
		response->statusCode = statusCode;
		response->contentType = contentType;
		response->rawContent = *rawContent;

		return response;
	}

	std::shared_ptr<HttpResponse> fromFile(std::shared_ptr<HttpStatusCode> statusCode,
			std::shared_ptr<File::File> file)
	{
		return fromString(statusCode, file->getContentType(), file->getContent());
	}
};

}

#endif /* HTTPRESPONSEFACTORY_HPP_ */
