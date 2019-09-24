#include "test.h"

#include <iostream>
#include <string>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "jengine_logging.h"

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
	testModelLoading();

	Jengine::Logging::jassert(false, "Help");

	this->chosen = const_cast<Jengine::VertexArray*>(this->model->vertexArray);
	//testVertexArray();
}

Test::~Test() {
	delete this->v;
}

bool Test::draw() {
	glClear(GL_DEPTH_BUFFER_BIT);
	renderer->drawTriangles(*this->chosen, *this->shader);
	return true;
}

bool Test::update()
{
	double px {0};
	double py {0};
	double speed = 10;
	if (this->input->keyPressed(JENGINE_KEY_W)) {
		px += this->deltaTime() * speed;
	}
	if (this->input->keyPressed(JENGINE_KEY_S)) {
		px -= this->deltaTime() * speed;
	}

	if (this->input->keyPressed(JENGINE_KEY_D)) {
		py -= this->deltaTime() * speed;
	}
	if (this->input->keyPressed(JENGINE_KEY_A)) {
		py += this->deltaTime() * speed;
	}

	glm::mat4 model = glm::rotate(glm::translate(glm::vec3{0,0, -7.0f}), angle, glm::normalize(glm::vec3{0.3f, 1.0f, 0}));
	this->camera->modifyPosition(glm::vec3{py, 0, px});
	glm::mat4 mvp = this->camera->getViewMatrix() * model;
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
/*
void Test::testScript() {
	Jengine::Script::Lexer lexer(Jengine::File::loadFileToString("../../res/scripts/ex1.jua"));
	Jengine::Script::Parser parser(lexer);
	Jengine::Script::Interpreter interpreter(parser);
	Jengine::Script::Token token = interpreter.run();
	std::cout << token.value.i << '\n';
}
*/

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
	this->model->enable();
	this->camera = new Jengine::Camera(static_cast<double>(glm::radians(60.0f)), this->renderer->width(), this->renderer->height(), 0.1, 100.0);
}
