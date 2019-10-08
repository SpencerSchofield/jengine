#ifndef JENGINE_LOGGING_H
#define JENGINE_LOGGING_H

#include "jengine_define.h"
#include <iostream>
#include <string>
#include "jengine_file.h"


#ifdef JENGINE_DEBUG
#define JENGINE_TRACE(...) Jengine::Logging::jtrace(__PRETTY_FUNCTION__,__FILE__,__LINE__,__VA_ARGS__)
#define JENGINE_DEBUG_LOG(...) Jengine::Logging::jdebug(__VA_ARGS__)
#else
#define JENGINE_TRACE(...)
#define JENGINE_DEBUG_LOG(...)
#endif
#define JENGINE_INFO(...) Jengine::Logging::jinfo(__VA_ARGS__)
#define JENGINE_WARN(...) Jengine::Logging::jwarn(__VA_ARGS__)
#define JENGINE_ERROR(...) Jengine::Logging::jerror(__VA_ARGS__)
#define JENGINE_FATAL(...) Jengine::Logging::jfatal(__VA_ARGS__)

#ifdef JENGINE_DEBUG
#define JENGINE_ASSERT(x, ...) Jengine::Logging::jassert((x), __VA_ARGS__)
#else
#define JENGINE_ASSERT(x, ...)
#endif



namespace Jengine {
	namespace Logging {

		enum class LEVEL {
			TRACE = 0,
			DEBUG,
			INFO,
			WARN,
			ERROR,
			FATAL,
			ASSERT,
		};
		UNIMPLEMENTED static LEVEL LOGGING_LEVEL;

		std::string createMessage(LEVEL logLevel, const std::string& msg);

		template <typename... T>
		std::string jmsg(std::string msg, T... msgParams) {
			std::vector<std::string> msgParamsList = {
				[](T x){
					if constexpr (std::is_arithmetic<T>::value) {
						return std::to_string(x);
					}
					else {
						return x;
					}
				}(msgParams)...
			};
			return File::replaceBetweenIndexed(msg, '{', '}', msgParamsList);
		}

		////////////////////////
		/// Trace //////////////
		////////////////////////
		template <typename... T>
		void jtrace(const std::string& func, const std::string& file, int line,
					const std::string& msg, T... msgParams) {
			std::cout << createMessage(LEVEL::TRACE,
									   jmsg(func + " - \"" + file + "\" line: " + std::to_string(line)
											+ " - "
+ msg, msgParams...));
		}

		////////////////////////
		/// Debug //////////////
		////////////////////////
		template <typename... T>
		void jdebug(std::string msg, T... msgParams) {
			std::cout << createMessage(LEVEL::DEBUG, jmsg(msg, msgParams...));
		}

		////////////////////////
		/// Info ///////////////
		////////////////////////
		template <typename... T>
		void jinfo(std::string msg, T... msgParams) {
			std::cout << createMessage(LEVEL::INFO, jmsg(msg, msgParams...));
		}

		////////////////////////
		/// Warn ///////////////
		////////////////////////
		template <typename... T>
		void jwarn(std::string msg, T... msgParams) {
			std::cout << createMessage(LEVEL::WARN, jmsg(msg, msgParams...));
		}

		////////////////////////
		/// Error //////////////
		////////////////////////
		template <typename... T>
		void jerror(std::string msg, T... msgParams) {
			std::cout << createMessage(LEVEL::ERROR, jmsg(msg, msgParams...));
		}

		////////////////////////
		/// Fatal //////////////
		////////////////////////
		template <typename... T>
		void jfatal(std::string msg, T... msgParams) {
			std::cout << createMessage(LEVEL::FATAL, jmsg(msg, msgParams...));
			exit(-1);
		}

		////////////////////////
		/// Assert /////////////
		////////////////////////
		template <typename... T>
		void jassert(bool x, std::string msg, T... msgParams) {
			if (x) {
				return;
			}
			std::cout << createMessage(LEVEL::ASSERT, jmsg(msg, msgParams...));
			exit(-1);
		}
	}

} // namespace Jengine

#endif // JENGINE_LOGGING_H
