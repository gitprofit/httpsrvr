/*
 * HttpStatusCode.hpp
 *
 *  Created on: Jun 15, 2013
 *      Author: michal
 */

#ifndef HTTPSTATUSCODE_HPP_
#define HTTPSTATUSCODE_HPP_

#include <string>
#include <vector>
#include <memory>

#include "../Util/Enum.hpp"

namespace Net
{

class HttpStatusCode : public Util::Enum<HttpStatusCode>
{
private:

	HttpStatusCode(const std::string& stringForm) :
		Enum(stringForm) { }

public:

	static const std::shared_ptr<HttpStatusCode> OK;
	static const std::shared_ptr<HttpStatusCode> NotFound;
	static const std::shared_ptr<HttpStatusCode> NotImplemented;

	static const std::vector< std::shared_ptr<HttpStatusCode> > values;
};

}

#endif /* HTTPSTATUSCODE_HPP_ */
