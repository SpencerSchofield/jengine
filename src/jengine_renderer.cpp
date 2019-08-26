#include "jengine_renderer.h"

namespace Jengine {

	Renderer::Renderer(const char* name, int width, int height)
	{
		glfwInit();
		this->window = glfwCreateWindow(width, height, name, nullptr, nullptr);
		glfwMakeContextCurrent(this->window);
		glewInit();
	}

	Renderer::~Renderer() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Renderer::startFrame()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::endFrame()
	{
		glfwSwapBuffers(this->window);
		glfwPollEvents();
	}

	void Renderer::setClearColor(float r, float g, float b, float a)
	{
		this->color = {r, g, b, a};
		glClearColor(r, g, b, a);
	}

	void Renderer::clearColor(float& r, float& g, float& b, float& a)
	{
		r = this->color.r;
		g = this->color.g;
		b = this->color.b;
		a = this->color.a;
	}

} // namespace Jengine
