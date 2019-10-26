#include "jengine.h"

extern Jengine::Application* jengine;

int main (
		[[gnu::unused]] int argc,
		[[gnu::unused]] char** argv)
{

	while (!jengine->finished && !jengine->renderer->shouldClose()) {
		jengine->currTime = glfwGetTime();
		jengine->renderer->startFrame();
		jengine->update(jengine->deltaTime());
		jengine->renderer->endFrame();
		jengine->input->getEvents();
		jengine->prevTime = jengine->currTime;
	}
}
