/*
 * NetException.hpp
 *
 *  Created on: May 16, 2013
 *      Author: michal
 */

#ifndef NETEXCEPTION_HPP_
#define NETEXCEPTION_HPP_

#include <stdexcept>
#include <cstdio>
#include <cerrno>

namespace Net
{

class NetException: public std::runtime_error
{
public:

	NetException(std::string message) :
			std::runtime_error(message.c_str())
	{
		if (errno != 0)
			::perror("perror");
	}

	NetException(std::string where, std::string what) :
			NetException("in " + where + ": " + what)
	{
	}

};

}

#endif /* NETEXCEPTION_HPP_ */
