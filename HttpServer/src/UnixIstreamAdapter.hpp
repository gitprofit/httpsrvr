/*
 * UnixIstreamAdapter.hpp
 *
 *  Created on: May 19, 2013
 *      Author: michal
 */

#ifndef UNIXISTREAMADAPTER_HPP_
#define UNIXISTREAMADAPTER_HPP_

/*
 * http://artofcode.wordpress.com/2010/12/12/deriving-from-stdstreambuf/
 */

#include <iostream>
#include <streambuf>
#include <unistd.h>

namespace
{

class UnixStreambuf: public std::streambuf
{
private:

	int streamFD;

	char currentChar;
	int bytesRead;

	void next()
	{
		bytesRead = ::read(streamFD, &currentChar, 1);
	}

public:

	UnixStreambuf(int unixFileDescriptor)
	{
		streamFD = unixFileDescriptor;
		next();
	}

	int_type underflow()
	{
		if(bytesRead == 0) return traits_type::eof();
	    return traits_type::to_int_type(currentChar);
	}

	int_type uflow()
	{
		if(bytesRead == 0) return traits_type::eof();
		char tmp = currentChar;
		next();
	    return traits_type::to_int_type(tmp);
	}

	int_type pbackfail(int_type)
	{
		return traits_type::eof();
	}

	std::streamsize showmanyc()
	{
	    return 0;
	}
};

}

#endif /* UNIXISTREAMADAPTER_HPP_ */
