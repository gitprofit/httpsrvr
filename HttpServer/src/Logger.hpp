/*
 * Logger.hpp
 *
 *  Created on: May 16, 2013
 *      Author: michal
 */

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

class Logger
{
private:

	Logger() = default;
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

public:

	static Logger& getInstance()
	{
		static Logger instance;

		return instance;
	}

	void log(std::string message)
	{
		std::cout << "logger: " << message << "\n";
	}
};

#endif /* LOGGER_HPP_ */
