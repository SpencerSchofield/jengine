#include "jengine_model.h"

#include "jengine_file.h"

namespace Jengine {

	Model::Model(VertexArray* vertexArray)
		: vertexArray(vertexArray) {

	}

	Model Model::loadOBJ(const std::string& fileName) {
		std::vector<float> positionData;
		std::vector<float> vt;
		std::vector<float> normalData;
		std::vector<unsigned int> indexData;
		std::vector<std::string> file = File::splitByDelimeter(File::loadFileToString(fileName), "\n");
		unsigned long found;
		unsigned long ofound;
		unsigned long slashFound;
		unsigned long oslashFound;
		// Use split by delimeter instead?
		//std::vector<float> tmpF;
		//std::vector<unsigned int> tmpI;
		for (unsigned int i = 0; i < file.size(); ++i) {
			switch (file[i][0]) {
				case 'v':
					switch (file[i][1]) {
						case ' ':
							ofound = 2;
							found = file[i].find(' ', ofound);
							positionData.push_back(std::stof(file[i].substr(ofound, found - ofound)));
							ofound = found + 1;
							found = file[i].find(' ', ofound);
							positionData.push_back(std::stof(file[i].substr(ofound, found - ofound)));
							ofound = found + 1;
							positionData.push_back(std::stof(file[i].substr(ofound)));
						break;
						case 't':
							ofound = 3;
							found = file[i].find(' ', ofound);
							vt.push_back(std::stof(file[i].substr(ofound, found - ofound)));
							ofound = found + 1;
							vt.push_back(std::stof(file[i].substr(ofound)));
						break;
						case 'n':
							ofound = 3;
							found = file[i].find(' ', ofound);
							normalData.push_back(std::stof(file[i].substr(ofound, found - ofound)));
							ofound = found + 1;
							found = file[i].find(' ', ofound);
							normalData.push_back(std::stof(file[i].substr(ofound, found - ofound)));
							ofound = found + 1;
							normalData.push_back(std::stof(file[i].substr(ofound)));
						break;
					}
				break;
				case 'f':
					ofound = 2;
					while (ofound != 0) {
						oslashFound = ofound;
						found = file[i].find(' ', ofound);
						slashFound = file[i].find('/', oslashFound);
						indexData.push_back(static_cast<unsigned int>(std::stoul(file[i].substr(oslashFound, slashFound - oslashFound))));
						oslashFound = slashFound + 1;
						slashFound = file[i].find('/', oslashFound);
						indexData.push_back(static_cast<unsigned int>(std::stoul(file[i].substr(oslashFound, slashFound - oslashFound))));
						oslashFound = slashFound + 1;
						indexData.push_back(static_cast<unsigned int>(std::stoul(file[i].substr(oslashFound))));
						ofound = found + 1;
					}
				break;
			}
		}
		return Model(new VertexArray(
					new VertexBuffer(&positionData[0], positionData.size() * sizeof(float), USE::STATIC_DRAW),
					 new IndexBuffer(&indexData[0], indexData.size())));
	}

} // namespace Jengine
