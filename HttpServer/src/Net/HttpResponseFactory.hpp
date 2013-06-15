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

	HttpResponse create()
	{


		return HttpResponse();
	}
};

}

#endif /* HTTPRESPONSEFACTORY_HPP_ */
