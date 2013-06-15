/*
 * EnumDefinitions.cpp
 *
 *  Created on: Jun 15, 2013
 *      Author: michal
 */

#include "Net/HttpStatusCode.hpp"

namespace Net
{
	const HttpStatusCode HttpStatusCode::OK("200 OK");
	const HttpStatusCode HttpStatusCode::NotFound("404 Not Found");
	const HttpStatusCode HttpStatusCode::NotImplemented("501 Not Implemented");
}
