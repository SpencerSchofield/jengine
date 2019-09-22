#include "test.h"

#include <iostream>
#include <string>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

template<>
void Jengine::Shader::setUniformMatrix<4,4>(std::string, unsigned int, float*);

Test::Test() : Jengine::Application(
		{"Test", 1280, 720, true, true, true, Jengine::Input::CURSOR_MODE::DISABLED}
		) {
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

bool Test::onStartup() {
	testModelLoading();
	this->chosen = const_cast<Jengine::VertexArray*>(this->model->vertexArray);
	//testVertexArray();
	return true;
}

bool Test::onShutdown() {
	delete this->v;
	return true;
}

bool Test::draw() {
	glClear(GL_DEPTH_BUFFER_BIT);
	renderer->drawTriangles(*this->chosen, *this->shader);
	return true;
}

bool Test::update()
{
	if (this->input->keyPressed(JENGINE_KEY_W)) {
		px += this->deltaTime() * 10;
	}
	if (this->input->keyPressed(JENGINE_KEY_S)) {
		px -= this->deltaTime() * 10;
	}

	if (this->input->keyPressed(JENGINE_KEY_D)) {
		py -= this->deltaTime() * 10;
	}
	if (this->input->keyPressed(JENGINE_KEY_A)) {
		py += this->deltaTime() * 10;
	}



	glm::mat4 model(1.0f);
	model = glm::translate(model, {0,0, -7.0f});
	model = glm::rotate(model, angle, glm::normalize(glm::vec3{0.3f, 1.0f, 0}));
	glm::mat4 view(1.0f);// = glm::lookAt(glm::vec3{0,0,px},glm::vec3{0,0,-7},glm::vec3{0,1,0});
	view = glm::translate(view, glm::vec3{py, 0, px});
	glm::mat4 perspective = glm::perspective(glm::radians(60.0f), this->renderer->aspectRatio(), 0.1f, 100.0f);
	glm::mat4 mvp = perspective * view * model;
	this->shader->setUniformMatrix<4,4>("mvp", 1, &mvp[0][0]);


	if (this->input->keyPressed(JENGINE_KEY_LEFT_SHIFT)) {
		if (this->input->keyPressed(JENGINE_KEY_Q)) {
			testModelLoading();
			this->chosen = const_cast<Jengine::VertexArray*>(this->model->vertexArray);
		}
		if (this->input->keyPressed(JENGINE_KEY_E)) {
			testVertexArray();
			this->chosen = const_cast<Jengine::VertexArray*>(this->v);
		}
	}

	if (this->input->keyPressed(JENGINE_KEY_ESCAPE)) {
		this->finished = true;
	}

	Jengine::Input::MousePosition r = this->input->getRelativeMousePosition();
	this->x.x -= r.x * this->deltaTime();
	this->x.y += r.y * this->deltaTime();

	//std::cout << this->deltaTime() << '\n';

	angle += 0.1f;
	return true;
}

void Test::testScript() {
	Jengine::Script::Lexer lexer(Jengine::File::loadFileToString("../../res/scripts/ex1.jua"));
	Jengine::Script::Parser parser(lexer);
	Jengine::Script::Interpreter interpreter(parser);
	Jengine::Script::Token token = interpreter.run();
	std::cout << token.value.i << '\n';
}

void Test::testVertexArray() {

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
		2,1,0,
		3,2,0,

		// front face
		4,5,6,
		4,6,7,

		// left face
		0,4,7,
		0,7,3,

		// right face
		6,5,1,
		2,6,1,

		// top face
		0,1,5,
		0,5,4,

		// bottom face
		3,7,6,
		3,6,2
	};

	this->v = new Jengine::VertexArray(new Jengine::VertexBuffer(pos, sizeof(pos), Jengine::USE::STATIC_DRAW),
									   new Jengine::IndexBuffer(index, sizeof(index)/sizeof(unsigned int)));
	this->shader = new Jengine::Shader("../../res/shaders/shader.vert", "../../res/shaders/shader.frag");

	this->v->vertexBuffer->addAttribute(Jengine::ATTRIBUTE_TYPE::FLOAT, 3);
	this->v->vertexBuffer->addAttribute(Jengine::ATTRIBUTE_TYPE::FLOAT, 4);
	this->v->vertexBuffer->createAttributes();
	(*this->v->vertexBuffer)[0].enable();
	(*this->v->vertexBuffer)[1].enable();
}

void Test::testModelLoading() {
	this->model = Jengine::Model::loadOBJ("../../res/models/teapot.obj");
	this->shader = new Jengine::Shader("../../res/shaders/shader.vert", "../../res/shaders/shader.frag");
	this->model->vertexArray->vertexBuffer->addAttribute(Jengine::ATTRIBUTE_TYPE::FLOAT, 3);
	this->model->vertexArray->vertexBuffer->createAttributes();
	(*this->model->vertexArray->vertexBuffer)[0].enable();
}
