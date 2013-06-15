/*
 * FileException.hpp
 *
 *  Created on: Jun 15, 2013
 *      Author: michal
 */

#ifndef FILEEXCEPTION_HPP_
#define FILEEXCEPTION_HPP_

#include <string>

#include "../Util/Exception.hpp"

namespace File
{

class FileException : public Util::Exception
{
public:

	FileException(const std::string& message) :
		Util::Exception(message) { }

	FileException(const std::string& where, const std::string& what) :
		Util::Exception(where, what) { }
};

}

#endif /* FILEEXCEPTION_HPP_ */
