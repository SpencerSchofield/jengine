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

	this->model = Jengine::Model::loadOBJ("../../res/models/man.obj");
	this->shader = new Jengine::Shader("../../res/shaders/shader.vert", "../../res/shaders/shader.frag");
	this->camera = new Jengine::Camera(static_cast<double>(glm::radians(60.0f)), this->renderer->width(), this->renderer->height(), 0.1, 1000.0);
}

Test::~Test() {
}

void Test::update(double deltaTime)
{
	double px {0};
	double py {0};
	double pz {0};
	double speed {30};
	if (this->input->keyPressed(JENGINE_KEY_W)) {
		pz += deltaTime * speed;
	}
	if (this->input->keyPressed(JENGINE_KEY_S)) {
		pz -= deltaTime * speed;
	}

	if (this->input->keyPressed(JENGINE_KEY_D)) {
		px -= deltaTime * speed;
	}
	if (this->input->keyPressed(JENGINE_KEY_A)) {
		px += deltaTime * speed;
	}
	if (this->input->keyPressed(JENGINE_KEY_ESCAPE)) {
		this->finished = true;
	}

	if (this->input->keyPressed(JENGINE_KEY_LEFT_CONTROL)) {
		py -= deltaTime * speed;
	}
	if (this->input->keyPressed(JENGINE_KEY_SPACE)) {
		py += deltaTime * speed;
	}

	glm::mat4 transform = glm::rotate(glm::translate(glm::scale(glm::vec3{0.001f, 0.001f, 0.001f}),glm::vec3{0, 0, -20.0f}), angle, glm::normalize(glm::vec3{0.3f, 1.0f, 0}));
	this->camera->modifyPosition(glm::vec3{px, py, pz});

	this->renderer->renderQueue(camera);
	this->renderer->push(model, &transform, shader);
	this->renderer->renderFlush();

	Jengine::Input::MousePosition r = this->input->getRelativeMousePosition();
	this->x.x -= r.x * deltaTime;
	this->x.y += r.y * deltaTime;

	angle += 0.01f;
}
