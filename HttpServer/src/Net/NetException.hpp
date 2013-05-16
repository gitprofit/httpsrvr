/*
 * NetException.hpp
 *
 *  Created on: May 16, 2013
 *      Author: michal
 */

#ifndef NETEXCEPTION_HPP_
#define NETEXCEPTION_HPP_

#include <stdexcept>

namespace Net
{

class NetException : public std::runtime_error
{
public:

	NetException(std::string message)
	: std::runtime_error(message.c_str())
	{ }

	NetException(std::string where, std::string what)
	: NetException("in " + where + ": '" + what + "' failed")
	{ }

};

}

#endif /* NETEXCEPTION_HPP_ */
