/*
 * Enum.hpp
 *
 *  Created on: Jun 15, 2013
 *      Author: michal
 */

#ifndef ENUM_HPP_
#define ENUM_HPP_

#include <string>
#include <vector>
#include <memory>

#include "Exception.hpp"

namespace Util
{

/*
 * CRTP Enum <-> DerivedEnum
 */

template <typename DerviedEnum>
class Enum
{
protected:

	const std::string stringForm;

	Enum(const std::string& stringForm) :
		stringForm(stringForm) { }

public:

	const std::string& toString() const
	{
		return stringForm;
	}

	static std::shared_ptr<DerviedEnum> fromString(const std::string& stringForm)
	{
		// DerivedEnum MUST provide list of all instances
		// DerivedEnum::values of type:
		// static const std::vector< std::shared_ptr<DerviedEnum> > values;

		for(auto v : DerviedEnum::values)
			if(v->stringForm == stringForm)
				return v;

		throw Exception("Enum::fromString()", "'" + stringForm + "' not found");
	}
};

}

#endif /* ENUM_HPP_ */
