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

namespace Net
{

class HttpStatusCode
{
private:

	const std::string stringForm;

	HttpStatusCode(const std::string& stringForm) :
		stringForm(stringForm) { }

public:

	const std::string& toString() const
	{
		return stringForm;
	}

	static const std::shared_ptr<HttpStatusCode> OK;
	static const std::shared_ptr<HttpStatusCode> NotFound;
	static const std::shared_ptr<HttpStatusCode> NotImplemented;

	static const std::vector< std::shared_ptr<HttpStatusCode> > values;
};

}

#endif /* HTTPSTATUSCODE_HPP_ */
