#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "jengine_vertexarray.h"
#include "jengine_shader.h"
#include <memory>
#include "jengine_model.h"
#include "jengine_camera.h"
#include <vector>
#include <glm/glm.hpp>
#include <unordered_map>

namespace Jengine {

	class Renderer
	{
	public:
		Renderer(const char* name, int width, int height, bool vsync);
		virtual ~Renderer();
		void startFrame() const;
		void endFrame() const;
		void setClearColor(float r, float g, float b, float a);
		void clearColor(float& r, float& g, float& b, float& a) const;
		bool shouldClose() const;
		GLFWwindow* window;

		void renderQueue(Camera* camera);
		void push(Model* model, glm::mat4* transform, Shader* shader);
		void renderFlush();


		void drawTriangles(VertexArray* vertexArray, Shader* shader) const;
		void drawModel(Model* model, Shader* shader) const;

		int width() const;
		int height() const;
		float aspectRatio() const;
	private:
		struct {float r,g,b,a;} color;


		struct RenderEvent {
			Model* model;
			glm::mat4* transform;
			Shader* shader;
		};

		// render queue stuff
		Camera* currentCamera;
		std::unordered_map<Shader*, std::vector<RenderEvent>> queue;
		bool queueStarted {false};
	};

} // namespace Jengine

#endif // RENDERER_H
