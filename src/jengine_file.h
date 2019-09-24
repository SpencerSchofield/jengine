#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>

namespace Jengine::File {
	std::string loadFileToString(const std::string& filePath);
	std::vector<std::string> splitByDelimeter(std::string x, const std::string& delimeter);
	std::vector<std::string> splitByDelimeter(std::string x, char delimeter);
	std::string removeOccurences(std::string x, const std::string& remove);
	std::vector<std::string> extractBetween(const std::string& x, const std::string& start, const std::string& end);
	std::vector<std::string> extractBetween(const std::string& x, char start, char end);
	std::string replaceBetweenIndexed(std::string& x, const std::string& start, const std::string& end, const std::vector<std::string>& replacements);
	std::string replaceBetweenIndexed(std::string& x, char start, char end, const std::vector<std::string>& replacements);
} // namespace Jengine

#endif // FILE_H
