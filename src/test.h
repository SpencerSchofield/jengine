#ifndef TEST_H
#define TEST_H

#include "jengine.h"

extern Jengine::Application* jengine;

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
	void testModelLoading();

private:
	Jengine::VertexArray* v;
	Jengine::VertexArray* chosen;
	Jengine::Shader* shader;
	Jengine::Model* model;
	float angle {0.0f};
	Jengine::Input::MousePosition x;
	double px {0};
	double py {0};
};

Jengine::Application* jengine = new Test;

/*
 * glfwSetErrorCallback(void () int, const char*);
 *
 */

#endif // TEST_H
