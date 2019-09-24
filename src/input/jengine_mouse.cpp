#include "../pch.h"
#include "jengine_mouse.h"

namespace Jengine {
	namespace Input {

		double Mouse::xScrollRel {0};

		Mouse::Mouse(GLFWwindow* window)
			: window(window){
			glfwSetScrollCallback(this->window, scrollCallback);
		}

		void Mouse::setCursorMode(CURSOR_MODE mode) const {
			glfwSetInputMode(this->window, GLFW_CURSOR, static_cast<int>(mode));
		}

		void Mouse::setRawMotion(bool raw) const {
			glfwSetInputMode(this->window, GLFW_RAW_MOUSE_MOTION, raw ? 1 : 0);
		}

		MousePosition Mouse::getMousePosition() {
			MousePosition pos;
			glfwGetCursorPos(this->window, &pos.x, &pos.y);
			this->oPosition = pos;
			return pos;
		}

		MousePosition Mouse::getRelativeMousePosition() {
			MousePosition pos = oPosition;
			glfwGetCursorPos(this->window, &this->oPosition.x, &this->oPosition.y);
			return {this->oPosition.x - pos.x, this->oPosition.y - pos.y};
		}

		bool Mouse::mouseButtonClicked(int button) const {
			return glfwGetMouseButton(this->window, button) == GLFW_PRESS;
		}

		double Mouse::getMouseScroll() const {
			return xScrollRel;
		}

		void Mouse::scrollCallback([[gnu::unused]] GLFWwindow* window, [[gnu::unused]] double xoff, double yoff) {
			xScrollRel = yoff;
		}

	} // namespace Input
} // namespace Jengine
