#include "jengine_renderer.h"


// debug only
#ifdef JENGINE_DEBUG
#include <iostream>
#endif

namespace Jengine {

	Renderer::Renderer(const char* name, int width, int height, bool vsync) {
		if (!glfwInit())
				std::cout << "could not initialize glfw";
		this->window = glfwCreateWindow(width, height, name, nullptr, nullptr);
		glfwMakeContextCurrent(this->window);

		// VSYNC
		glfwSwapInterval(vsync ? 1 : 0);
		#ifdef JENGINE_DEBUG
		if (glewInit() != GLEW_OK) {
			std::cout << "could not initialize glew";
		}
		#else
		glewInit();
		#endif
	}

	Renderer::~Renderer() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Renderer::startFrame() const {
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::endFrame() const {
		glfwSwapBuffers(this->window);
		glfwPollEvents();
	}

	void Renderer::setClearColor(float r, float g, float b, float a) {
		this->color = {r, g, b, a};
		glClearColor(r, g, b, a);
	}

	void Renderer::clearColor(float& r, float& g, float& b, float& a) const {
		r = this->color.r;
		g = this->color.g;
		b = this->color.b;
		a = this->color.a;
	}

	bool Renderer::shouldClose() const {
		return glfwWindowShouldClose(this->window);
	}

	void Renderer::drawTriangles(VertexArray& vertexArray, Shader& shader) const {
		shader.bind();
		vertexArray.bind();
		glDrawElements(GL_TRIANGLES, static_cast<int>(vertexArray.indexBuffer->getCount()), GL_UNSIGNED_INT, nullptr);
	}

	int Renderer::width() const {
		int width;
		glfwGetWindowSize(this->window, &width, nullptr);
		return width;
	}

	int Renderer::height() const {
		int height;
		glfwGetWindowSize(this->window, nullptr, &height);
		return height;
	}

	float Renderer::aspectRatio() const {
		int width, height;
		glfwGetWindowSize(this->window, &width, &height);
		return width / static_cast<float>(height);
	}

} // namespace Jengine
