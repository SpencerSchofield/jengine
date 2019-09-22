#include "jengine.h"

extern Jengine::Application* jengine;

int main ([[gnu::unused]] int argc, [[gnu::unused]] char** argv) {
	jengine->onStartup();

	while (!jengine->finished && !jengine->renderer->shouldClose()) {
		jengine->currTime = glfwGetTime();
		jengine->update();
		jengine->renderer->startFrame();
		jengine->draw();
		jengine->renderer->endFrame();
		jengine->input->getEvents();
		jengine->prevTime = jengine->currTime;
	}

	jengine->onShutdown();
}
