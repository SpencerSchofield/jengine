#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "jengine_vertexarray.h"
#include "jengine_shader.h"
#include <memory>

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

		void drawTriangles(VertexArray& vertexArray);

		int width();
		int height();
		float aspectRatio();
	private:
		GLFWwindow* window;
		struct {float r,g,b,a;} color;
	};

} // namespace Jengine

#endif // RENDERER_H
