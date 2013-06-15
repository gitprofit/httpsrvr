/*
 * File.hpp
 *
 *  Created on: Jun 15, 2013
 *      Author: michal
 */

#ifndef FILE_HPP_
#define FILE_HPP_

#include <memory>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "../Net/HttpContentType.hpp"

namespace File
{

// references
class FileManager;

class File
{
	friend class FileManager;

private:

	File() = default;

	std::shared_ptr<Net::HttpContentType> contentType;
	std::shared_ptr<std::string> absolutePath;

public:

	std::shared_ptr<Net::HttpContentType> getContentType()
	{
		return contentType;
	}

	std::shared_ptr<std::string> getContent()
	{
		auto out = std::make_shared<std::string>();

		std::ifstream file(*absolutePath);
		file.unsetf(std::ios::skipws);
		std::istream_iterator<char> eos;
		std::istream_iterator<char> it(file);
		std::copy(it, eos, std::back_inserter(*out));

		return out;
	}
};

}

#endif /* FILE_HPP_ */
