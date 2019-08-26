#ifndef SHADER_H
#define SHADER_H


namespace Jengine {

	class Shader
	{
	public:
		Shader(const char* vertex, const char* fragment);
		~Shader();
		void bind();

	private:

		unsigned int compileShader(const char* filePath, unsigned int shaderType);

		unsigned int glId;
		static unsigned int currentlybound;
	};

} // namespace Jengine

#endif // SHADER_H
