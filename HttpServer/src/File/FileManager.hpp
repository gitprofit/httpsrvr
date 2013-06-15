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

#include "File.hpp"
#include "FileException.hpp"

namespace File
{

class FileManager
{
private:

	std::string rootDir;

	bool fileExists(const std::string& absolutePath)
	{
		std::ifstream file(absolutePath);
		return file;
	}

public:

	FileManager(const std::string& rootDir) :
		rootDir(rootDir) { }

	std::shared_ptr<File> getFile(const std::string& relativePath)
	{
		auto absolutePath = std::make_shared<std::string>(rootDir + relativePath);

		if((*absolutePath).back() == '/')
		{
			// check for defaults: index.html, index.htm, ...

			if(fileExists(*absolutePath + "index.html"))
				*absolutePath += "index.html";

			else if(fileExists(*absolutePath + "index.htm"))
				*absolutePath += "index.htm";
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
