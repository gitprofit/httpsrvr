/*
 * HttpRequest.hpp
 *
 *  Created on: May 16, 2013
 *      Author: michal
 */

#ifndef HTTPREQUEST_HPP_
#define HTTPREQUEST_HPP_

#include "HttpMethod.hpp"

namespace Net
{

class HttpRequest
{
private:

	HttpMethod method;
	std::string URI;

public:

	HttpMethod getMethod()
	{
		return method;
	}

	std::string getURI()
	{
		return URI;
	}
};

}

#endif /* HTTPREQUEST_HPP_ */
