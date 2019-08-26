#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Jengine {

	class Renderer
	{
	public:
		Renderer(const char* name, int width, int height);
		virtual ~Renderer();
		void startFrame();
		void endFrame();
		void setClearColor(float r, float g, float b, float a);
		void clearColor(float& r, float& g, float& b, float& a);
	private:
		GLFWwindow* window;
		struct {float r,g,b,a;} color;
	};

} // namespace Jengine

#endif // RENDERER_H
