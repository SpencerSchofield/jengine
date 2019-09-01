#include "test.h"

#include <iostream>
#include <string>
#include <stdio.h>

Test::Test() : Jengine::Application("Test", 1280, 720) {

}

bool Test::onStartup() {
	float pos[] = {
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,

		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f
	};

	unsigned int index[] = {
		// back face
		0,1,2,
		0,2,3,

		// front face
		4,5,6,
		4,6,7,

		// left face
		0,4,7,
		0,7,3,

		// right face
		1,5,6,
		1,6,2,

		// top face
		0,1,5,
		0,5,4,

		// bottom face
		3,7,6,
		3,6,2
	};
	this->d = new Jengine::VertexBuffer(pos, sizeof(pos), Jengine::USE::STATIC_DRAW);
	this->n = new Jengine::IndexBuffer(index, sizeof(index)/sizeof(unsigned int));

	this->d->bind();
	this->n->bind();
	this->program = new Jengine::Shader("../../res/shaders/shader.vert", "../../res/shaders/shader.frag");

	//this->v = new Jengine::VertexArray(this->d, this->n, this->program);

	this->program->bind();

	this->d->addAttribute(Jengine::ATTRIBUTE_TYPE::FLOAT, 3);
	(*this->d)[0].enable();
	this->renderer->setClearColor(0, 0, 0, 1);

	glBindBuffer(GL_ARRAY_BUFFER, this->d->glId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->n->glId);
	glUseProgram(this->program->glId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, nullptr);


	glBegin(GL_TRIANGLES);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();

	// Jengine Script test
	/*
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
	*/
}

bool Test::onShutdown()
{
	delete this->d;
	delete this->program;
}

bool Test::draw()
{
	//renderer->drawTriangles(*this->v);
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
}

bool Test::update()
{

}

