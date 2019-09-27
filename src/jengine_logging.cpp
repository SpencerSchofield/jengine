#include "jengine_logging.h"


namespace Jengine {
	namespace Logging {

		std::string createMessage(LEVEL logLevel, const std::string& msg) {
			std::string x[] = {
				"[TRACE]  ",
				"[DEBUG]  ",
				"[INFO]   ",
				"[WARN]   ",
				"[ERROR]  ",
				"[FATAL]  ",
				"[ASSERT] "
			};
			return x[static_cast<unsigned long>(logLevel)] + msg + '\n';
		}
	}
}
