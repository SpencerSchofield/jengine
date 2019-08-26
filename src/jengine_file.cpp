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

} // namespace Jengine
