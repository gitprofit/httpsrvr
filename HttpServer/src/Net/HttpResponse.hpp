/*
 * HttpResponse.hpp
 *
 *  Created on: May 17, 2013
 *      Author: michal
 */

#ifndef HTTPRESPONSE_HPP_
#define HTTPRESPONSE_HPP_

#include <string>
#include <memory>

#include "HttpStatusCode.hpp"
#include "HttpContentType.hpp"

namespace Net
{

// references
class HttpResponseFactory;
//class HttpStatusCode;
//class HttpContentType;

class HttpResponse
{
	friend class HttpResponseFactory;

private:

	HttpResponse() = default;

	std::shared_ptr<HttpStatusCode> statusCode;
	std::shared_ptr<HttpContentType> contentType;
	std::string serverName;
	std::string rawContent;

public:

	std::string toString()
	{
		std::ostringstream oss;
		oss.unsetf(std::ios::skipws);

		/*	HTTP/1.1 200 OK\r\n
			Server: Apache/1.3.3.7 (Unix) (Red-Hat/Linux)\r\n
			Content-Length: {content_length}\r\n
			Connection: close\r\n
			Content-Type: text/html; charset=UTF-8\r\n\r\n
			the content of which length is equal to {content_length}
		 */

		oss << "HTTP/1.1 " << statusCode->toString() << "\r\n";
		oss << "Server: " << serverName << "\r\n";
		oss << "ContentLength: " << rawContent.size() << "\r\n";
		oss << "ContentType: " << contentType->toString() << "\r\n";
		oss << "\r\n";
		oss << rawContent;

		return oss.str();
	}
};

}

#endif /* HTTPRESPONSE_HPP_ */
