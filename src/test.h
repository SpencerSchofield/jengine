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

private:
	Jengine::VertexBuffer* d;
	Jengine::Shader* program;
};

Jengine::Application* jengine = new Test;

#endif // TEST_H
