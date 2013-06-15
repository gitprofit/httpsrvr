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

public:

	RequestHandler(
			std::shared_ptr<Net::Socket> socket,
			std::shared_ptr<Net::HttpRequestFactory> requestFactory,
			std::shared_ptr<Net::HttpResponseFactory> responseFactory,
			std::shared_ptr<File::FileManager> fileManager) :
				socket(socket),
				requestFactory(requestFactory),
				responseFactory(responseFactory),
				fileManager(fileManager)
	{
		//
	}

	virtual void run()
	{
		try
		{
			auto request = socket->read(requestFactory);

			auto f = fileManager->getFile((*request)["URI"]);

			auto rsp = responseFactory->fromFile(Net::HttpStatusCode::OK, f);

			socket->write(rsp);

			std::cout << "connection closed!\n";

			socket->close();
		}
		catch (Util::Exception& ex)
		{
			socket->close();
			std::cout << ex.what() << "\n";
		}
	}
};

#endif /* REQUESTHANDLER_HPP_ */
