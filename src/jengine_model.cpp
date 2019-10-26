#include "jengine_model.h"

#include "jengine_file.h"
#include "jengine_logging.h"

#ifdef JENGINE_DEBUG
#include <iostream>
#endif

namespace Jengine {

	Model::Model(
			VertexArray* vertexArray)
		: vertexArray(vertexArray)
	{

		this->vertexArray->vertexBuffer->addAttribute(Jengine::ATTRIBUTE_TYPE::FLOAT, 3);
		this->vertexArray->vertexBuffer->createAttributes();
	}

	Model::~Model()
	{
		delete this->vertexArray;
	}

	void Model::enable() const
	{
		(*this->vertexArray->vertexBuffer)[0].enable();
	}

	Model* Model::loadOBJ(
			const std::string& fileName)
	{
		std::vector<float> positionData;
		std::vector<float> vt;
		std::vector<float> normalData;
		std::vector<unsigned int> positionIndex;
		std::vector<unsigned int> vtIndex;
		std::vector<unsigned int> normalIndex;
		std::vector<std::string> file = File::splitByDelimeter(File::loadFileToString(fileName), '\n');
		unsigned long found;
		unsigned long ofound;
		unsigned long slashFound;
		unsigned long oslashFound;
		// Use split by delimeter instead?
		//std::vector<float> tmpF;
		//std::vector<unsigned int> tmpI;
		for (unsigned int i = 0; i < file.size(); ++i) {

			#ifdef JENGINE_DEBUG
			if (!(i % 100000)) {
				std::cout << i << '/' << file.size() << '\n';
			}
			#endif

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
						default:
							JENGINE_INFO("Model({0}): Type not supported - {1}", fileName, file[i]);
						break;
					}
				break;
				case 'f':
					ofound = 2;
					while (ofound != 0) {
						oslashFound = ofound;
						found = file[i].find(' ', ofound);
						slashFound = file[i].find('/', oslashFound);
						positionIndex.push_back(
							static_cast<unsigned int>(
							std::stoul(file[i].substr(oslashFound, slashFound - oslashFound)))-1);
						oslashFound = slashFound + 1;
						slashFound = file[i].find('/', oslashFound);
						if (slashFound - oslashFound != 0)
							vtIndex.push_back(
								static_cast<unsigned int>(
								std::stoul(file[i].substr(oslashFound, slashFound - oslashFound)))-1);
						oslashFound = slashFound + 1;
						normalIndex.push_back(
							static_cast<unsigned int>(
							std::stoul(file[i].substr(oslashFound)))-1);
						ofound = found + 1;
					}
				break;
				default:
					JENGINE_INFO("Model({0}): {1} - data ignored", fileName, file[i]);
				break;
			}
		}
		return new Model(new VertexArray(
			new VertexBuffer(&positionData[0], positionData.size() * sizeof(float),
				USE::STATIC_DRAW),
			new IndexBuffer(&positionIndex[0], positionIndex.size())));
	}


} // namespace Jengine
