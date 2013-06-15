/*
 * EnumDefinitions.cpp
 *
 *  Created on: Jun 15, 2013
 *      Author: michal
 */

#include "Net/HttpStatusCode.hpp"

namespace Net
{
	//const HttpStatusCode HttpStatusCode::OK("200 OK");
	//const HttpStatusCode HttpStatusCode::NotFound("404 Not Found");
	//const HttpStatusCode HttpStatusCode::NotImplemented("501 Not Implemented");

	const std::shared_ptr<HttpStatusCode> HttpStatusCode::OK(new HttpStatusCode("200 OK"));
	const std::shared_ptr<HttpStatusCode> HttpStatusCode::NotFound(new HttpStatusCode("404 Not Found"));
	const std::shared_ptr<HttpStatusCode> HttpStatusCode::NotImplemented(new HttpStatusCode("501 Not Implemented"));
}
