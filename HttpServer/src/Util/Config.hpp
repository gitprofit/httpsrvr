/*
 * Config.hpp
 *
 *  Created on: Jun 14, 2013
 *      Author: michal
 */

#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <string>
#include <fstream>
#include <map>

#include "Exception.hpp"

namespace Util
{

class Config
{
private:

	std::map<std::string, std::string> settings;

public:

	Config(const std::string& configFile)
	{
		settings.clear();

		std::ifstream file(configFile.c_str());

		if(!file) throw Exception("Config::Config()", "file not found");

		std::string line;

		while(std::getline(file, line))
		{
			auto start = line.find(": ");
			auto name = line.substr(0, start);
			auto value = line.substr(start + 2);
			settings[name] = value;
		}
	}

	std::string operator[](const std::string& optionName)
	{
		auto it = settings.find(optionName);

		if (it == settings.end())
			throw Exception("Config::operator[]",
					"option '" + optionName + "' not found");

		return it->second;
	}
};

}

#endif /* CONFIG_HPP_ */
