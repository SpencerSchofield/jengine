#include "jengine_file.h"

namespace Jengine::File {

	std::string loadFileToString(const std::string& filePath) {
		FILE* file = fopen(filePath.c_str(), "rb");
		if (!file)
			return "";
		std::fseek(file, 0, SEEK_END);
		int length = std::ftell(file);
		std::fseek(file, 0, SEEK_SET);
		length -= std::ftell(file);
		char* buffer = new char[length+1];
		std::fread(buffer, 1, length, file);
		buffer[length] = '\0';
		std::string out(buffer);
		delete [] buffer;
		return out;
	}

	std::vector<std::string> splitByDelimeter(std::string x, const std::string& delimeter) {
		std::vector<std::string> out;
		int found = 0;
		while ((found = x.find(delimeter, found)) != -1) {
			if (found)
				out.emplace_back(x.substr(0,found+1));
			x.erase(0, found+1);
		}
		return out;
	}

	std::string removeOccurences(std::string x, const std::string& remove) {
		int found = 0;
		while ((found = x.find(remove, found)) != -1) {
			x.erase(found, remove.length());
		}
		return x;
	}

} // namespace Jengine
