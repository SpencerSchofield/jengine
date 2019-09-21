#include "jengine.h"

extern Jengine::Application* jengine;

int main (int argc, char** argv) {
	jengine->onStartup();

	while (!jengine->finished && !jengine->renderer->shouldClose()) {
		jengine->update();
		jengine->renderer->startFrame();
		jengine->draw();
		jengine->renderer->endFrame();
		jengine->input->getEvents();
	}

	jengine->onShutdown();
}
