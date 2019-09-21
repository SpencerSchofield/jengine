#ifndef TEST_H
#define TEST_H

#include "jengine.h"


class Test : public Jengine::Application
{
public:
	Test();

	bool onStartup() override;
	bool onShutdown() override;
	bool draw() override;
	bool update() override;


	void testScript();
	void testVertexArray();

private:
	Jengine::VertexArray* v;
	float angle {0.0f};
};

Jengine::Application* jengine = new Test;

/*
 * glfwSetErrorCallback(void () int, const char*);
 * Application::deltaTime();
 *
 */

#endif // TEST_H
