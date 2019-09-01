#include "test.h"

#include <iostream>
#include <string>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

Test::Test() : Jengine::Application("Test", 640, 480) {

}

bool Test::onStartup() {
	float pos[] = {

		// back verticies
		-1.0f, -1.0f, -1.0f,	1.0f,1.0f,1.0f,1.0f,
		1.0f, -1.0f, -1.0f,		1.0f,0.0f,0.0f,1.0f,
		1.0f, 1.0f, -1.0f,		0.0f,1.0f,0.0f,1.0f,
		-1.0f, 1.0f, -1.0f,		0.0f,0.0f,1.0f,1.0f,

		// front verticies
		-1.0f, -1.0f, 1.0f,		1.0f,1.0f,1.0f,1.0f,
		1.0f, -1.0f, 1.0f,		1.0f,0.0f,0.0f,1.0f,
		1.0f, 1.0f, 1.0f,		0.0f,1.0f,0.0f,1.0f,
		-1.0f, 1.0f, 1.0f,		0.0f,0.0f,1.0f,1.0f
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

	this->v = new Jengine::VertexArray(new Jengine::VertexBuffer(pos, sizeof(pos), Jengine::USE::STATIC_DRAW),
									   new Jengine::IndexBuffer(index, sizeof(index)/sizeof(unsigned int)),
									   new Jengine::Shader("../../res/shaders/shader.vert", "../../res/shaders/shader.frag"));

	this->v->vertexBuffer->addAttribute(Jengine::ATTRIBUTE_TYPE::FLOAT, 3);
	this->v->vertexBuffer->addAttribute(Jengine::ATTRIBUTE_TYPE::FLOAT, 4);
	(*this->v->vertexBuffer)[0].enable();
	(*this->v->vertexBuffer)[1].enable();
	glm::mat4 mvp(1.0f);
	//glm::vec3 tmp(0.1f, 9.0f, 4.2f);
	//tmp = glm::normalize(tmp);
	glm::mat4 model(1.0f);// = glm::rotate(45.0f, tmp);
	glm::mat4 view(1.0f);
	glm::mat4 perspective = glm::perspective(60.0f, this->renderer->aspectRatio(), 0.1f, 10.0f);
	mvp = model * view * perspective;
	this->v->shader->setUniformMatrix<4,4>("mvp", 1, &mvp[0][0]);
	this->renderer->setClearColor(0, 0, 0, 1);
}

bool Test::onShutdown()
{
	delete this->v;
}

bool Test::draw()
{
	renderer->drawTriangles(*this->v);
}

bool Test::update()
{

}

