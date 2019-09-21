#include "jengine_application.h"

namespace Jengine {

	Application::Application(Application_Config config)
		: config(config) {
		latestApplication = this;
		this->renderer = new Jengine::Renderer(this->config.name,
											   this->config.width,
											   this->config.height,
											   this->config.vsync);
		if (this->config.continuousEvents) {
			this->input = new Jengine::Input::Input(this->renderer->window, glfwPollEvents);
		}
		else {
			this->input = new Jengine::Input::Input(this->renderer->window, glfwWaitEvents);
		}

		this->input->setRawMotion(this->config.rawMotion);
		this->input->setCursorMode(this->config.cursorMode);

	}


	Application::~Application() {
		delete this->renderer;
	}

}
