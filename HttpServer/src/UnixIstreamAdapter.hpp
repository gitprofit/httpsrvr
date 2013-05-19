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


class UnixStreambuf : public std::streambuf
{
	friend class UnixIstreamAdapter;

private:

	int streamFD;

	char currentChar;
	int bytesRead;
	int stopc;

	UnixStreambuf(int unixFileDescriptor)
	{
		streamFD = unixFileDescriptor;
		stopc = 0;
		next();
	}

	void next()
	{
		bytesRead = ::read(streamFD, &currentChar, 1);

		if(currentChar != '\r' && currentChar != '\n') stopc = 0;
		else stopc++;
	}

	virtual int_type underflow()
	{
		if(stopc > 3) return traits_type::eof();
	    return traits_type::to_int_type(currentChar);
	}

	virtual int_type uflow()
	{
		if(stopc > 3) return traits_type::eof();
		char tmp = currentChar;
		next();
	    return traits_type::to_int_type(tmp);
	}

	virtual int_type pbackfail(int_type)
	{
		return traits_type::eof();
	}

	virtual std::streamsize showmanyc()
	{
	    return 0;
	}
};


class UnixIstreamAdapter : public std::istream
{

private:

	UnixStreambuf sb;

public:

	UnixIstreamAdapter(int unixFileDescriptor)
	: std::istream(&sb), sb(unixFileDescriptor) { }
};

#endif /* UNIXISTREAMADAPTER_HPP_ */
