#include "jengine_shader.h"

#include "jengine_file.h"
#include <GL/glew.h>

#include <iostream>

#include "jengine_logging.h"

namespace Jengine {

	Shader::Shader(
			const char* vertex,
			const char* fragment)
	{
		this->glId = glCreateProgram();
		unsigned int vertexId = compileShader(vertex, GL_VERTEX_SHADER);
		unsigned int fragmentId = compileShader(fragment, GL_FRAGMENT_SHADER);

		glAttachShader(this->glId, vertexId);
		glAttachShader(this->glId, fragmentId);
		glLinkProgram(this->glId);

		glValidateProgram(this->glId);

		int status;
		glGetProgramiv(this->glId, GL_LINK_STATUS, &status);

		if (!status) {
			int length;
			glGetProgramiv(this->glId, GL_INFO_LOG_LENGTH, &length);
			char* log = new char[length];
			glGetProgramInfoLog(this->glId, length, &length, log);

			// log
			//std::cout << log << '\n';

			delete [] log;
			glDeleteProgram(this->glId);
			this->glId = 0;
		}
		glDetachShader(this->glId, vertexId);
		glDetachShader(this->glId, fragmentId);
		glDeleteShader(vertexId);
		glDeleteShader(fragmentId);

		glUseProgram(this->glId);
	}

	Shader::~Shader()
	{
		glDeleteProgram(this->glId);
	}

	void Shader::bind() const
	{
		//JENGINE_TRACE("");
		glUseProgram(this->glId);
	}

	int Shader::getLocation(
			std::string name)
	{
		if (uniformLocationCache.find(name) == uniformLocationCache.end()) {
			uniformLocationCache[name] = glGetUniformLocation(this->glId, name.c_str());
		}
		return uniformLocationCache[name];
	}

	unsigned int Shader::compileShader(
			const char* filePath,
			unsigned int shaderType)
	{
		std::string file = Jengine::File::loadFileToString(filePath);
		unsigned int id = glCreateShader(shaderType);
		const char* src = file.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);
		int status;
		glGetShaderiv(id, GL_COMPILE_STATUS, &status);
		if (!status) {
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* log = new char[length];
			glGetShaderInfoLog(id, length, &length, log);

			// log

			std::cout << log << '\n';

			delete [] log;
			glDeleteShader(id);
			return 0;
		}
		return id;
	}
} // namespace Jengine
