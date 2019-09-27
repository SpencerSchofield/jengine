#include "test.h"

#include <iostream>
#include <string>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "jengine_logging.h"

Test::Test() : Jengine::Application(
		{"Test", 1280, 720, true, true, true, Jengine::Input::CURSOR_MODE::DISABLED}
		) {

	this->model = Jengine::Model::loadOBJ("../../res/models/teapot.obj");
	this->shader = new Jengine::Shader("../../res/shaders/shader.vert", "../../res/shaders/shader.frag");
	this->camera = new Jengine::Camera(static_cast<double>(glm::radians(60.0f)), this->renderer->width(), this->renderer->height(), 0.1, 1000.0);
}

Test::~Test() {
}

void Test::update(double deltaTime)
{
	double px {0};
	double py {0};
	double speed {10};
	if (this->input->keyPressed(JENGINE_KEY_W)) {
		px += deltaTime * speed;
	}
	if (this->input->keyPressed(JENGINE_KEY_S)) {
		px -= deltaTime * speed;
	}

	if (this->input->keyPressed(JENGINE_KEY_D)) {
		py -= deltaTime * speed;
	}
	if (this->input->keyPressed(JENGINE_KEY_A)) {
		py += deltaTime * speed;
	}
	if (this->input->keyPressed(JENGINE_KEY_ESCAPE)) {
		this->finished = true;
	}


	glm::mat4 transform = glm::rotate(glm::translate(glm::vec3{0,-150.0f, -200.0f}), angle, glm::normalize(glm::vec3{0.3f, 1.0f, 0}));
	glm::mat4 transforms[10000];

	this->camera->modifyPosition(glm::vec3{py, 0, px});

	this->renderer->renderQueue(camera);

	for (int i = 0; i < 10000; i++) {
		transforms[i] = glm::translate(transform, {(i / 100) * 3, (i % 100) * 3, 0});
		this->renderer->push(model, &transforms[i], shader);
	}
	this->renderer->renderFlush();

	Jengine::Input::MousePosition r = this->input->getRelativeMousePosition();
	this->x.x -= r.x * deltaTime;
	this->x.y += r.y * deltaTime;

	angle += 0.1f;
}
