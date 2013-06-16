/*
 * FileManager.hpp
 *
 *  Created on: Jun 15, 2013
 *      Author: michal
 */

#ifndef FILEMANAGER_HPP_
#define FILEMANAGER_HPP_

#include <memory>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

#include "File.hpp"
#include "FileException.hpp"
#include "../Util/Config.hpp"

namespace File
{

class FileManager
{
private:

	std::shared_ptr<Util::Config> config;
	std::string rootDir;
	std::vector<std::string> defaultFiles;

	bool fileExists(const std::string& absolutePath)
	{
		std::ifstream file(absolutePath);
		return file;
	}

public:

	FileManager(std::shared_ptr<Util::Config> config) :
		config(config)
	{
		rootDir = (*config)["wwwroot"];
		std::istringstream iss((*config)["Default-Files"]);
		std::istream_iterator<std::string> eos;
		std::istream_iterator<std::string> it(iss);
		std::copy(it, eos, std::back_inserter(defaultFiles));
	}

	std::shared_ptr<File> getFile(const std::string& relativePath)
	{
		auto absolutePath = std::make_shared<std::string>(rootDir + relativePath);

		// check for defaults: index.html, index.htm, ...
		if((*absolutePath).back() == '/')
			for(auto& defFile : defaultFiles)
				if(fileExists(*absolutePath + defFile))
				{
					*absolutePath += defFile;
					break;
				}

		if(!fileExists(*absolutePath))
			throw FileException("FileManager::getFile()", "file '" + relativePath + "' not found");

		auto file = std::shared_ptr<File>(new File());
		file->absolutePath = absolutePath;

		auto extBegin = relativePath.find_last_of(".");
		auto extension = relativePath.substr(extBegin+1);

		file->contentType = Net::HttpContentType::TextPlain;
		for(auto ct : Net::HttpContentType::values)
			for(auto ext : ct->extensions)
				if(ext == extension)
				{
					file->contentType = ct;
					break;
				}

		return file;
	}
};

}

#endif /* FILEMANAGER_HPP_ */
