#ifndef TEST_H
#define TEST_H

#include "jengine.h"

extern Jengine::Application* jengine;

class Test : public Jengine::Application
{
public:
	Test();
	~Test() override;
	void update(double deltaTime) override;

private:
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
