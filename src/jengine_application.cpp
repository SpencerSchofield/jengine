#include "jengine_application.h"

namespace Jengine {

	Application::Application(const char* name, int width, int height) {
		latestApplication = this;
		this->renderer = new Jengine::Renderer(name, width, height);
	}


	Application::~Application() {
		delete this->renderer;
	}

}
