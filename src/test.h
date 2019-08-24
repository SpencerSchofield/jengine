#ifndef TEST_H
#define TEST_H

#include "jengine.h"

class Test : public Jengine::Application
{
public:
	Test();

	bool onStartup() override;
};

Jengine::Application* jengine = new Test;

#endif // TEST_H
