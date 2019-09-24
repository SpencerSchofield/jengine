#include "jengine_camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "jengine_define.h"

namespace Jengine {

	Camera::Camera(double fov, double width, double height, double near, double far)
		: projection(glm::perspective(fov, width/height, near, far)), position(glm::mat4{1.0f}), updated(false) {
		// Perspective
	}

	Camera::Camera(double left, double right, double bottom, double top, double near, double far)
		: projection(glm::ortho(left, right, bottom, top, near, far)), position(glm::mat4{1.0f}), view(projection * position){
		// Ortho
	}

	glm::mat4 Camera::getViewMatrix() {
		if (!updated) {
			// rebuild the view matrix
			this->view = projection * position;
		}
		return this->view;
	}

	void Camera::setPosition(UNIMPLEMENTED glm::vec3 position) {
	}

	void Camera::setAngle(UNIMPLEMENTED glm::vec3 angle) {
	}

	void Camera::setPositionAndAngle(glm::mat4 matrix) {
		this->position = matrix;
	}

	UNSURE void Camera::modifyPosition(UNIMPLEMENTED glm::vec3 position) {
		this->position = glm::translate(this->position, position);
	}

	void Camera::modifyAngle(UNIMPLEMENTED glm::vec3 angle) {

	}

	UNSURE void Camera::modifyPositionAndAngle(glm::mat4 matrix) {
		this->position += matrix;
		this->updated = false;
	}

} // namespace Jengine
