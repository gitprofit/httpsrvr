/*
 * HttpMethod.hpp
 *
 *  Created on: Jun 15, 2013
 *      Author: michal
 */

#ifndef HTTPMETHOD_HPP_
#define HTTPMETHOD_HPP_

#include <string>
#include <vector>
#include <memory>

#include "../Util/Enum.hpp"

namespace Net
{

class HttpMethod : public Util::Enum<HttpMethod>
{
private:

	HttpMethod(const std::string& stringForm) :
		Enum(stringForm) { }

public:

	static const std::shared_ptr<HttpMethod> GET;
	static const std::shared_ptr<HttpMethod> POST;

	static const std::vector< std::shared_ptr<HttpMethod> > values;
};

}

#endif /* HTTPMETHOD_HPP_ */
