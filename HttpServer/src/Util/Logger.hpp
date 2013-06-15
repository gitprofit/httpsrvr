/*
 * Logger.hpp
 *
 *  Created on: May 16, 2013
 *      Author: michal
 */

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <iostream>

namespace Util
{

class Logger
{
private:
	std::ostream& os;

public:

	Logger(std::ostream& os) :
		os(os) { }

	void log(const std::string& message)
	{
		os << "logger: " << message << "\n";
	}
};

}

#endif /* LOGGER_HPP_ */
