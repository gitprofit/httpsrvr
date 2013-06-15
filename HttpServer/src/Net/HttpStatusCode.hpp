/*
 * HttpStatusCode.hpp
 *
 *  Created on: Jun 15, 2013
 *      Author: michal
 */

#ifndef HTTPSTATUSCODE_HPP_
#define HTTPSTATUSCODE_HPP_

#include <string>

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

	static const HttpStatusCode OK;
	static const HttpStatusCode NotFound;
	static const HttpStatusCode NotImplemented;
};

}

#endif /* HTTPSTATUSCODE_HPP_ */
