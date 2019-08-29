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
	Jengine::Script::Expression c(2);
	Jengine::Script::Expression op1(Jengine::Script::Operator::TYPE::MULTIPLY, &a, &b);
	Jengine::Script::Expression op2 (Jengine::Script::Operator::TYPE::ADD, &op1, &c);
	Jengine::Script::Number x;
	Jengine::Script::Expression op3(Jengine::Script::Operator::ASSIGN, x, &op2);
	op3.value();
	double output = x.value;//Jengine::Script::Number(op2.value()).value;
	//std::cout << output << '\n';

	Jengine::Script::createProgram(Jengine::File::loadFileToString("../../res/scripts/ex1.jua"));
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

