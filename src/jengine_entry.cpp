#include "jengine.h"

extern Jengine::Application* jengine;

int main (int argc, char** argv) {
	jengine->onStartup();

	while (!jengine->finished) {
		jengine->update();
		jengine->draw();
	}

	jengine->onShutdown();
}
