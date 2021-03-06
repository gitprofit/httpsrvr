/*
 * HttpContentType.hpp
 *
 *  Created on: Jun 15, 2013
 *      Author: michal
 */

#ifndef HTTPCONTENTTYPE_HPP_
#define HTTPCONTENTTYPE_HPP_

#include <string>
#include <vector>
#include <memory>
#include <initializer_list>

#include "../Util/Enum.hpp"

namespace Net
{

class HttpContentType : public Util::Enum<HttpContentType>
{
private:

	HttpContentType(const std::string& MIME, const std::initializer_list<std::string>& extensions) :
		Enum(MIME), extensions(extensions) { }

public:

	const std::vector<std::string> extensions;

	static const std::shared_ptr<HttpContentType> TextHtml;
	static const std::shared_ptr<HttpContentType> TextXml;
	static const std::shared_ptr<HttpContentType> TextPlain;
	static const std::shared_ptr<HttpContentType> TextCss;
	static const std::shared_ptr<HttpContentType> ImagePng;
	static const std::shared_ptr<HttpContentType> ImageGif;
	static const std::shared_ptr<HttpContentType> ImageJpg;
	static const std::shared_ptr<HttpContentType> ImageJpeg;
	static const std::shared_ptr<HttpContentType> ApplicationZip;

	static const std::vector< std::shared_ptr<HttpContentType> > values;
};

}

#endif /* HTTPCONTENTTYPE_HPP_ */
