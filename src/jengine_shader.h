#ifndef SHADER_H
#define SHADER_H

#include <unordered_map>
#include <string>

namespace Jengine {

	class Shader
	{
	public:
		Shader(const char* vertex, const char* fragment);
		~Shader();

		void setUniform(std::string name, float a);
		void setUniform(std::string name, int a);
		void setUniform(std::string name, unsigned int a);
		void setUniform(std::string name, float a, float b);
		void setUniform(std::string name, int a, int b);
		void setUniform(std::string name, unsigned int a, unsigned int b);
		void setUniform(std::string name, float a, float b, float c);
		void setUniform(std::string name, int a, int b, int c);
		void setUniform(std::string name, unsigned int a, unsigned int b, unsigned int c);
		void setUniform(std::string name, float a, float b, float c, float d);
		void setUniform(std::string name, int a, int b, int c, int d);
		void setUniform(std::string name, unsigned int a, unsigned int b, unsigned int c, unsigned int d);
		template <int, typename T>
		void setUniformArray(std::string name, unsigned int count, T* data);

		template <int, int>
		void setUniformMatrix(std::string name, unsigned int count, float* data);

		void bind() const;

	private:

		unsigned int glId;

		inline int getLocation(std::string name);

		unsigned int compileShader(const char* filePath, unsigned int shaderType);

		std::unordered_map<std::string, int> uniformLocationCache;
	};

} // namespace Jengine

#endif // SHADER_H
