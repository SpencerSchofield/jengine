#include "jengine_renderer.h"
#include "jengine_logging.h"

// debug only
#ifdef JENGINE_DEBUG
#include <iostream>
#endif

#include <algorithm>

template<>
void Jengine::Shader::setUniformMatrix<4,4>(std::string, unsigned int, glm::mat4*);

namespace Jengine {

	Renderer::Renderer(const char* name, int width, int height, bool vsync) {
		if (!glfwInit()) {
			JENGINE_FATAL("GLFW could not be inilialised");
		}
		this->window = glfwCreateWindow(width, height, name, nullptr, nullptr);
		glfwMakeContextCurrent(this->window);

		// VSYNC
		glfwSwapInterval(vsync ? 1 : 0);
		if (glewInit() != GLEW_OK) {
			JENGINE_FATAL("Glew could not be initialised");
		}

		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		JENGINE_INFO("Culling enabled for back faces");
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		JENGINE_INFO("Depth testing enabled");
	}

	Renderer::~Renderer() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Renderer::startFrame() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

	void Renderer::renderQueue(Camera* camera) {
		this->currentCamera = camera;
		this->queueStarted = true;
	}

	void Renderer::push(Model* model, glm::mat4* transform, Shader* shader) {
		JENGINE_ASSERT(this->queueStarted, "Tried pushing before starting renderQueue");
		this->queue.push_back({model, transform, shader});
	}

	void Renderer::renderFlush() {
		JENGINE_ASSERT(this->queueStarted, "Tried flushing before starting renderQueue");
		glm::mat4 camera = this->currentCamera->getViewMatrix();
		std::sort(this->queue.begin(), this->queue.end(), [](RenderEvent& a, RenderEvent& b){
			return a.shader - b.shader;
		});
		[[maybe_unused]] unsigned long numVerticies {0};
		Shader* currentShader {nullptr};
		for (unsigned long i = 0; i < this->queue.size(); i++) {
			RenderEvent& currentEvent = this->queue[i];
			if (currentEvent.shader != currentShader) {
				currentEvent.shader->bind();
				currentEvent.shader->setUniformMatrix<4,4>("vp", 1, &camera);
			}
			currentEvent.shader->setUniformMatrix<4,4>("model", 1, this->queue[i].transform);
			currentEvent.model->enable();
			glDrawElements(GL_TRIANGLES,
						   static_cast<int>(currentEvent.model->vertexArray->indexBuffer->getCount()),
						   GL_UNSIGNED_INT, nullptr);
			#ifdef JENGINE_DEBUG
			numVerticies += currentEvent.model->vertexArray->indexBuffer->getCount();
			#endif
		}
		this->queue.clear();
		this->queueStarted = false;
		JENGINE_DEBUG_LOG("{0} verticies rendered", numVerticies);
	}

	void Renderer::drawTriangles(VertexArray* vertexArray, Shader* shader) const {
		shader->bind();
		vertexArray->bind();
		glDrawElements(GL_TRIANGLES, static_cast<int>(vertexArray->indexBuffer->getCount()), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::drawModel(Model* model, Shader* shader) const {
		drawTriangles(model->vertexArray, shader);
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
