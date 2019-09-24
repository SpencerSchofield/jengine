#ifndef JENGINE_LOGGING_H
#define JENGINE_LOGGING_H

#include "jengine_define.h"
#include <iostream>
#include <string>
#include <initializer_list>
#include "jengine_file.h"

//#define JENGINE_ASSERT(x, msg, ...) Jengine::Logging::jassert((x), (msg), (__VA_ARGS__))

namespace Jengine {
	namespace Logging {

		template <typename... T>
		void jassert(bool x, std::string msg, T... msgParams) {
			if (x)
				return;
			std::vector<std::string> msgParamsList = {msgParams...};

			std::cout << "ASSERT: " << File::replaceBetweenIndexed(msg, '{', '}', msgParamsList) << '\n';
		}

		enum class LEVEL {
			WARNING,
			ERROR,
			VERBOSE
		};
		UNIMPLEMENTED static LEVEL LOGGING_LEVEL;
	}


} // namespace Jengine

#endif // JENGINE_LOGGING_H
