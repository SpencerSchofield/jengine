#include "jengine_shader.h"

#include "jengine_file.h"
#include <GL/glew.h>

//#include <iostream>

namespace Jengine {

	Shader::Shader(const char* vertex, const char* fragment)
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

	Shader::~Shader() {
		glDeleteProgram(this->glId);
	}

	void Shader::onBind() {
		glUseProgram(this->glId);
	}

	inline int Shader::getLocation(std::string name) {
		if (uniformLocationCache.find(name) == uniformLocationCache.end()) {
			uniformLocationCache[name] = glGetUniformLocation(this->glId, name.c_str());
		}
		return uniformLocationCache[name];
	}

	unsigned int Shader::compileShader(const char* filePath, unsigned int shaderType) {
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

			//std::cout << log << '\n';

			delete [] log;
			glDeleteShader(id);
			return 0;
		}
		return id;
	}

	void Shader::setUniform(std::string name, float a) {
		glUniform1f(getLocation(name), a);
	}

	void Shader::setUniform(std::string name, int a) {
		glUniform1i(getLocation(name), a);
	}

	void Shader::setUniform(std::string name, unsigned int a) {
		glUniform1ui(getLocation(name), a);
	}

	void Shader::setUniform(std::string name, float a, float b) {
		glUniform2f(getLocation(name), a, b);
	}

	void Shader::setUniform(std::string name, int a, int b) {
		glUniform2i(getLocation(name), a, b);
	}

	void Shader::setUniform(std::string name, unsigned int a, unsigned int b) {
		glUniform2ui(getLocation(name), a, b);
	}

	void Shader::setUniform(std::string name, float a, float b, float c) {
		glUniform3f(getLocation(name), a, b, c);
	}

	void Shader::setUniform(std::string name, int a, int b, int c) {
		glUniform3i(getLocation(name), a, b, c);
	}

	void Shader::setUniform(std::string name, unsigned int a, unsigned int b, unsigned int c) {
		glUniform3ui(getLocation(name), a, b, c);
	}

	void Shader::setUniform(std::string name, float a, float b, float c, float d) {
		glUniform4f(getLocation(name), a, b, c, d);
	}

	void Shader::setUniform(std::string name, int a, int b, int c, int d) {
		glUniform4i(getLocation(name), a, b, c, d);
	}

	void Shader::setUniform(std::string name, unsigned int a, unsigned int b, unsigned int c, unsigned int d) {
		glUniform4ui(getLocation(name), a, b, c, d);
	}

	template <>
	void Shader::setUniformArray<1,float>(std::string name, unsigned int count, float* data) {
		glUniform1fv(getLocation(name), count, data);
	}

	template <>
	void Shader::setUniformArray<1,int>(std::string name, unsigned int count, int* data) {
		glUniform1iv(getLocation(name), count, data);
	}

	template <>
	void Shader::setUniformArray<1,unsigned int>(std::string name, unsigned int count, unsigned int* data) {
		glUniform1uiv(getLocation(name), count, data);
	}

	template <>
	void Shader::setUniformArray<2,float>(std::string name, unsigned int count, float* data) {
		glUniform2fv(getLocation(name), count, data);
	}

	template <>
	void Shader::setUniformArray<2,int>(std::string name, unsigned int count, int* data) {
		glUniform2iv(getLocation(name), count, data);
	}

	template <>
	void Shader::setUniformArray<2,unsigned int>(std::string name, unsigned int count, unsigned int* data) {
		glUniform2uiv(getLocation(name), count, data);
	}

	template <>
	void Shader::setUniformArray<3,float>(std::string name, unsigned int count, float* data) {
		glUniform3fv(getLocation(name), count, data);
	}

	template <>
	void Shader::setUniformArray<3,int>(std::string name, unsigned int count, int* data) {
		glUniform3iv(getLocation(name), count, data);
	}

	template <>
	void Shader::setUniformArray<3,unsigned int>(std::string name, unsigned int count, unsigned int* data) {
		glUniform3uiv(getLocation(name), count, data);
	}

	template <>
	void Shader::setUniformArray<4,float>(std::string name, unsigned int count, float* data) {
		glUniform4fv(getLocation(name), count, data);
	}

	template <>
	void Shader::setUniformArray<4,int>(std::string name, unsigned int count, int* data) {
		glUniform4iv(getLocation(name), count, data);
	}

	template <>
	void Shader::setUniformArray<4,unsigned int>(std::string name, unsigned int count, unsigned int* data) {
		glUniform4uiv(getLocation(name), count, data);
	}

	template <>
	void Shader::setUniformMatrix<2,2>(std::string name, unsigned int count, float* data) {
		glUniformMatrix2fv(getLocation(name), count, false, data);
	}

	template <>
	void Shader::setUniformMatrix<2,3>(std::string name, unsigned int count, float* data) {
		glUniformMatrix2x3fv(getLocation(name), count, false, data);
	}

	template <>
	void Shader::setUniformMatrix<2,4>(std::string name, unsigned int count, float* data) {
		glUniformMatrix2x4fv(getLocation(name), count, false, data);
	}

	template <>
	void Shader::setUniformMatrix<3,3>(std::string name, unsigned int count, float* data) {
		glUniformMatrix3fv(getLocation(name), count, false, data);
	}

	template <>
	void Shader::setUniformMatrix<3,2>(std::string name, unsigned int count, float* data) {
		glUniformMatrix3x2fv(getLocation(name), count, false, data);
	}

	template <>
	void Shader::setUniformMatrix<3,4>(std::string name, unsigned int count, float* data) {
		glUniformMatrix3x4fv(getLocation(name), count, false, data);
	}

	template <>
	void Shader::setUniformMatrix<4,4>(std::string name, unsigned int count, float* data) {
		glUniformMatrix4fv(getLocation(name), count, false, data);
	}

	template <>
	void Shader::setUniformMatrix<4,2>(std::string name, unsigned int count, float* data) {
		glUniformMatrix4x2fv(getLocation(name), count, false, data);
	}

	template <>
	void Shader::setUniformMatrix<4,3>(std::string name, unsigned int count, float* data) {
		glUniformMatrix4x3fv(getLocation(name), count, false, data);
	}

	/*
	template <int, typename T>
	void Shader::setUniformArray(std::string name, unsigned int count, T*data) {
	}

	template <int, int>
	void setUniformMatrix(std::string name, unsigned int count, float* data) {
	}
	*/

} // namespace Jengine
