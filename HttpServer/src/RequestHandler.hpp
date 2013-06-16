/*
 * RequestHandler.hpp
 *
 *  Created on: Jun 15, 2013
 *      Author: michal
 */

#ifndef REQUESTHANDLER_HPP_
#define REQUESTHANDLER_HPP_

#include "Thread/Thread.hpp"

class RequestHandler :
		public Thread::Thread<Thread::DetachState::Detached, Thread::CancelType::Deferred>
{
private:

	std::shared_ptr<Net::Socket> socket;

	std::shared_ptr<Net::HttpRequestFactory> requestFactory;
	std::shared_ptr<Net::HttpResponseFactory> responseFactory;

	std::shared_ptr<File::FileManager> fileManager;

	std::shared_ptr<Util::Config> config;
	std::shared_ptr<Util::Logger> logger;

public:

	RequestHandler(
			std::shared_ptr<Net::Socket> socket,
			std::shared_ptr<Net::HttpRequestFactory> requestFactory,
			std::shared_ptr<Net::HttpResponseFactory> responseFactory,
			std::shared_ptr<File::FileManager> fileManager,
			std::shared_ptr<Util::Config> config,
			std::shared_ptr<Util::Logger> logger) :
				socket(socket),
				requestFactory(requestFactory),
				responseFactory(responseFactory),
				fileManager(fileManager),
				config(config),
				logger(logger)
	{
		//
	}

	virtual void run()
	{
		std::shared_ptr<Net::HttpRequest> request;

		try
		{
			request = socket->read(requestFactory);
		}
		catch(Util::Exception& ex)
		{
			logger->log(ex.what());

			auto response = responseFactory->error501();
			socket->write(response);
			socket->close();
			return;
		}

		std::shared_ptr<File::File> requestedFile;
		std::shared_ptr<Net::HttpStatusCode> statusCode;

		try
		{
			auto requestedFile = fileManager->getFile((*request)["URI"]);
			auto response = responseFactory->fromFile(Net::HttpStatusCode::OK, requestedFile);
			socket->write(response);
			socket->close();
			return;
		}
		catch(Util::Exception& ex)
		{
			logger->log(ex.what());

			auto response = responseFactory->error404();
			socket->write(response);
			socket->close();
			return;
		}
	}
};

#endif /* REQUESTHANDLER_HPP_ */
