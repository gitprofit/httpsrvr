/*
 * HttpResponse.hpp
 *
 *  Created on: May 17, 2013
 *      Author: michal
 */

#ifndef HTTPRESPONSE_HPP_
#define HTTPRESPONSE_HPP_

namespace Net
{

// references
class HttpResponseFactory;

class HttpResponse
{
	friend class HttpResponseFactory;

private:

	std::string statusCode;
	std::string contentType;
	std::string content;
};

}

#endif /* HTTPRESPONSE_HPP_ */
