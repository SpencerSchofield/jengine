#ifndef SHADER_H
#define SHADER_H

#include <unordered_map>
#include <string>
#include <glm/glm.hpp>

#include <glm/gtc/type_ptr.hpp>

namespace Jengine {

	class Shader
	{
	public:
		Shader(
				const char* vertex,
				const char* fragment);

		~Shader();
		template <typename T>
		void setUniform(
				std::string name,
				T a);
		template <typename T>
		void setUniform(
				std::string name,
				T a,
				T b);
		template <typename T>
		void setUniform(
				std::string name,
				T a,
				T b,
				T c);
		template <typename T>
		void setUniform(
				std::string name,
				T a,
				T b,
				T c,
				T d);
		template <int, typename T>
		void setUniformArray(
				std::string name,
				unsigned int count,
				T* data);
		template <int, int>
		void setUniformMatrix(
				std::string name,
				unsigned int count,
				glm::mat4* data);
		void bind() const;

	private:

		unsigned int glId;

		int getLocation(
				std::string name);
		unsigned int compileShader(
				const char* filePath,
				unsigned int shaderType);

		std::unordered_map<std::string, int> uniformLocationCache;
	};


	// Implementation

	template <>
	void Shader::setUniform<float>(
			std::string name,
			float a)
	{
		glUniform1f(getLocation(name), a);
	}

	template <>
	void Shader::setUniform<int>(
			std::string name,
			int a)
	{
		glUniform1i(getLocation(name), a);
	}

	template <>
	void Shader::setUniform<unsigned int>(
			std::string name,
			unsigned int a)
	{
		glUniform1ui(getLocation(name), a);
	}

	template <>
	void Shader::setUniform<float>(
			std::string name,
			float a,
			float b)
	{
		glUniform2f(getLocation(name), a, b);
	}

	template <>
	void Shader::setUniform<int>(
			std::string name,
			int a,
			int b)
	{
		glUniform2i(getLocation(name), a, b);
	}

	template <>
	void Shader::setUniform<unsigned int>(
			std::string name,
			unsigned int a,
			unsigned int b)
	{
		glUniform2ui(getLocation(name), a, b);
	}

	template <>
	void Shader::setUniform<float>(
			std::string name,
			float a,
			float b,
			float c)
	{
		glUniform3f(getLocation(name), a, b, c);
	}

	template <>
	void Shader::setUniform<int>(
			std::string name,
			int a,
			int b,
			int c)
	{
		glUniform3i(getLocation(name), a, b, c);
	}

	template <>
	void Shader::setUniform<unsigned int>(
			std::string name,
			unsigned int a,
			unsigned int b,
			unsigned int c)
	{
		glUniform3ui(getLocation(name), a, b, c);
	}

	template <>
	void Shader::setUniform<float>(
			std::string name,
			float a,
			float b,
			float c,
			float d)
	{
		glUniform4f(getLocation(name), a, b, c, d);
	}

	template <>
	void Shader::setUniform<int>(
			std::string name,
			int a,
			int b,
			int c,
			int d)
	{
		glUniform4i(getLocation(name), a, b, c, d);
	}

	template <>
	void Shader::setUniform<unsigned int>(
			std::string name,
			unsigned int a,
			unsigned int b,
			unsigned int c,
			unsigned int d)
	{
		glUniform4ui(getLocation(name), a, b, c, d);
	}

	template <>
	void Shader::setUniformArray<1,float>(
			std::string name,
			unsigned int count,
			float* data)
	{
		glUniform1fv(getLocation(name), count, data);
	}

	template <>
	void Shader::setUniformArray<1,int>(
			std::string name,
			unsigned int count,
			int* data)
	{
		glUniform1iv(getLocation(name), count, data);
	}

	template <>
	void Shader::setUniformArray<1,unsigned int>(
			std::string name,
			unsigned int count,
			unsigned int* data)
	{
		glUniform1uiv(getLocation(name), count, data);
	}

	template <>
	void Shader::setUniformArray<2,float>(
			std::string name,
			unsigned int count,
			float* data)
	{
		glUniform2fv(getLocation(name), count, data);
	}

	template <>
	void Shader::setUniformArray<2,int>(
			std::string name,
			unsigned int count,
			int* data)
	{
		glUniform2iv(getLocation(name), count, data);
	}

	template <>
	void Shader::setUniformArray<2,unsigned int>(
			std::string name,
			unsigned int count,
			unsigned int* data)
	{
		glUniform2uiv(getLocation(name), count, data);
	}

	template <>
	void Shader::setUniformArray<3,float>(
			std::string name,
			unsigned int count,
			float* data)
	{
		glUniform3fv(getLocation(name), count, data);
	}

	template <>
	void Shader::setUniformArray<3,int>(
			std::string name,
			unsigned int count,
			int* data)
	{
		glUniform3iv(getLocation(name), count, data);
	}

	template <>
	void Shader::setUniformArray<3,unsigned int>(
			std::string name,
			unsigned int count,
			unsigned int* data)
	{
		glUniform3uiv(getLocation(name), count, data);
	}

	template <>
	void Shader::setUniformArray<4,float>(
			std::string name,
			unsigned int count,
			float* data)
	{
		glUniform4fv(getLocation(name), count, data);
	}

	template <>
	void Shader::setUniformArray<4,int>(
			std::string name,
			unsigned int count,
			int* data)
	{
		glUniform4iv(getLocation(name), count, data);
	}

	template <>
	void Shader::setUniformArray<4,unsigned int>(
			std::string name,
			unsigned int count,
			unsigned int* data)
	{
		glUniform4uiv(getLocation(name), count, data);
	}

	template <>
	void Shader::setUniformMatrix<4,4>(
			std::string name,
			unsigned int count,
			glm::mat4* data)
	{
		glUniformMatrix4fv(getLocation(name), count, false, glm::value_ptr(data[0]));
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

#endif // SHADER_H
