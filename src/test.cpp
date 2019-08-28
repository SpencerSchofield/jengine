#include "test.h"

#include <iostream>
#include <string>
#include <stdio.h>

Test::Test() : Jengine::Application("Test", 1280, 720) {

}

bool Test::onStartup() {
	float pos[] = {-1.0f, -1.0f, 0.0f, 0.0f, 1.0f, -1.0f};
	this->d = new Jengine::VertexBuffer(pos, sizeof(pos), Jengine::USE::STATIC_DRAW);
	this->d->bind();
	this->program = new Jengine::Shader("../../res/shaders/shader.vert", "../../res/shaders/shader.frag");
	this->program->bind();
	this->d->addAttribute(Jengine::ATTRIBUTE_TYPE::FLOAT, 2);
	(*this->d)[0].enable();
	this->renderer->setClearColor(0, 0, 0, 1);


	// Jengine Script test

	Jengine::Script::Expression a(5);
	Jengine::Script::Expression b(10);
	Jengine::Script::Operator op(Jengine::Script::Operator::TYPE::ADD, &a, &b);
	double output = ((Jengine::Script::Number*)op.value())->value;
	std::cout << output << '\n';
}

bool Test::onShutdown()
{
	delete this->d;
	delete this->program;
}

bool Test::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

bool Test::update()
{

}

