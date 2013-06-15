/*
 * EnumDefinitions.cpp
 *
 *  Created on: Jun 15, 2013
 *      Author: michal
 */

//#include "Util/Enum.hpp"

#include "Net/HttpMethod.hpp"
#include "Net/HttpStatusCode.hpp"
#include "Net/HttpContentType.hpp"

namespace Net
{
	/*
	 * HttpMethod
	 */

	const std::shared_ptr<HttpMethod> HttpMethod::GET	(new HttpMethod("GET"));
	const std::shared_ptr<HttpMethod> HttpMethod::POST	(new HttpMethod("POST"));
	const std::vector< std::shared_ptr<HttpMethod> > HttpMethod::values =
	{
			HttpMethod::GET,
			HttpMethod::POST
	};


	/*
	 * HttpStatusCode
	 */

	const std::shared_ptr<HttpStatusCode> HttpStatusCode::OK			(new HttpStatusCode("200 OK"));
	const std::shared_ptr<HttpStatusCode> HttpStatusCode::NotFound		(new HttpStatusCode("404 Not Found"));
	const std::shared_ptr<HttpStatusCode> HttpStatusCode::NotImplemented(new HttpStatusCode("501 Not Implemented"));
	const std::vector< std::shared_ptr<HttpStatusCode> > HttpStatusCode::values =
	{
			HttpStatusCode::OK,
			HttpStatusCode::NotFound,
			HttpStatusCode::NotImplemented
	};


	/*
	 * HttpContentType
	 */

	const std::shared_ptr<HttpContentType> HttpContentType::TextHtml	(new HttpContentType("text/html", { "htm", "html" }));
	const std::shared_ptr<HttpContentType> HttpContentType::TextXml		(new HttpContentType("text/xml", { "xml" }));
	const std::shared_ptr<HttpContentType> HttpContentType::TextPlain	(new HttpContentType("text/plain", { "txt" }));
	const std::shared_ptr<HttpContentType> HttpContentType::TextCss		(new HttpContentType("text/css", { "css" }));
	const std::shared_ptr<HttpContentType> HttpContentType::ImagePng	(new HttpContentType("image/png", { "png" }));
	const std::shared_ptr<HttpContentType> HttpContentType::ImageGif	(new HttpContentType("image/gif", { "gif" }));
	const std::shared_ptr<HttpContentType> HttpContentType::ImageJpg	(new HttpContentType("image/jpg", { "jpg" }));
	const std::shared_ptr<HttpContentType> HttpContentType::ImageJpeg	(new HttpContentType("image/jpeg", { "jpeg" }));
	const std::shared_ptr<HttpContentType> HttpContentType::ApplicationZip(new HttpContentType("application/zip", { "zip" }));

	const std::vector< std::shared_ptr<HttpContentType> > HttpContentType::values =
	{
			HttpContentType::TextHtml,
			HttpContentType::TextHtml,
			HttpContentType::TextXml,
			HttpContentType::TextPlain,
			HttpContentType::TextCss,
			HttpContentType::ImagePng,
			HttpContentType::ImageGif,
			HttpContentType::ImageJpg,
			HttpContentType::ImageJpeg,
			HttpContentType::ApplicationZip
	};
}
