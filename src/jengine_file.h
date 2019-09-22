#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>

namespace Jengine::File {
	std::string loadFileToString(const std::string& filePath);
	std::vector<std::string> splitByDelimeter(std::string x, const std::string& delimeter);
	std::vector<std::string> splitByDelimeter(std::string x, char delimeter);
	std::string removeOccurences(std::string x, const std::string& remove);

} // namespace Jengine

#endif // FILE_H
