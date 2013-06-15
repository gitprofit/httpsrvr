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
/*
	static std::vector<const HttpStatusCode&> values()
	{
		std::vector<const HttpStatusCode&> out;
		out.push_back(HttpStatusCode::OK);
		out.push_back(HttpStatusCode::NotFound);
		out.push_back(HttpStatusCode::NotImplemented);

		return out;
	}
*/
	/*
	static const HttpStatusCode& getOK()
	{
		//std::vector<HttpStatusCode&> out;
		return OK;
	}*/

	static const std::shared_ptr<HttpStatusCode> OK;
	static const std::shared_ptr<HttpStatusCode> NotFound;
	static const std::shared_ptr<HttpStatusCode> NotImplemented;

	static std::vector< std::shared_ptr<HttpStatusCode> > values()
	{
		return { OK, NotFound, NotImplemented };
	}
};

}

#endif /* HTTPSTATUSCODE_HPP_ */
