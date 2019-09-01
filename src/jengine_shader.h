#ifndef SHADER_H
#define SHADER_H

#include "jengine_globject.h"

namespace Jengine {

	class Shader : public GLObject
	{
	public:
		Shader(const char* vertex, const char* fragment);
		~Shader() override;


	private:
		void onBind() override;

		unsigned int compileShader(const char* filePath, unsigned int shaderType);
	};

} // namespace Jengine

#endif // SHADER_H
