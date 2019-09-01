#include "jengine_renderer.h"


// debug only
#include <iostream>

namespace Jengine {

	Renderer::Renderer(const char* name, int width, int height)
	{
		if (!glfwInit())
				std::cout << "could not initialize glfw";
		this->window = glfwCreateWindow(width, height, name, nullptr, nullptr);
		glfwMakeContextCurrent(this->window);
		if (glewInit() != GLEW_OK)
			std::cout << "could not initialize glew";
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

	void Renderer::drawTriangles(VertexArray& vertexArray)
	{
		vertexArray.bind();
		glDrawElements(GL_TRIANGLES, vertexArray.indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);
	}

	int Renderer::width()
	{
		int width;
		glfwGetWindowSize(this->window, &width, nullptr);
		return width;
	}

	int Renderer::height()
	{
		int height;
		glfwGetWindowSize(this->window, nullptr, &height);
		return height;
	}

	float Renderer::aspectRatio() {
		int width, height;
		glfwGetWindowSize(this->window, &width, &height);
		return width / (float) height;
	}

} // namespace Jengine
