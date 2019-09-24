#ifndef TEST_H
#define TEST_H

#include "jengine.h"

extern Jengine::Application* jengine;

class Test : public Jengine::Application
{
public:
	Test();
	~Test() override;
	bool draw() override;
	bool update() override;


	//void testScript();
	void testVertexArray();
	void testModelLoading();

private:
	Jengine::VertexArray* v;
	Jengine::VertexArray* chosen;
	Jengine::Shader* shader;
	Jengine::Model* model;
	Jengine::Camera* camera;
	float angle {0.0f};
	Jengine::Input::MousePosition x;
};

Jengine::Application* jengine = new Test;

/*
 * glfwSetErrorCallback(void () int, const char*);
 *
 */

#endif // TEST_H
