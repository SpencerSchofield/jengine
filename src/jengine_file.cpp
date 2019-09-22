#include "jengine_file.h"

namespace Jengine::File {

	std::string loadFileToString(const std::string& filePath) {
		FILE* file = fopen(filePath.c_str(), "rb");
		if (!file)
			return "File not opened!";
		std::fseek(file, 0, SEEK_END);
		long length = std::ftell(file);
		std::fseek(file, 0, SEEK_SET);
		length -= std::ftell(file);
		char* buffer = new char[static_cast<unsigned long>(length+1)];
		std::fread(buffer, 1, static_cast<unsigned long>(length), file);
		buffer[length] = '\0';
		std::string out(buffer);
		delete [] buffer;
		return out;
	}

	std::vector<std::string> splitByDelimeter(std::string x, const std::string& delimeter) {
		std::vector<std::string> out;
		unsigned long found;
		unsigned long ofound = 0;
		while ((found = x.find(delimeter, ofound)) != std::string::npos) {
			out.emplace_back(x.substr(ofound,found - ofound));
			ofound = found + 1;
		}
		return out;
	}

	std::string removeOccurences(std::string x, const std::string& remove) {
		unsigned long found = 0;
		while ((found = x.find(remove, found)) != std::string::npos) {
			x.erase(found, remove.length());
		}
		return x;
	}

	std::vector<std::string> splitByDelimeter(std::string x, char delimeter)
	{
		std::vector<std::string> out;
		unsigned long found;
		unsigned long ofound = 0;
		while ((found = x.find(delimeter, ofound)) != std::string::npos) {
			out.emplace_back(x.substr(ofound,found - ofound));
			ofound = found + 1;
		}
		return out;
	}

} // namespace Jengine
