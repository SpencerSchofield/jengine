#include "jengine_keyboard.h"

namespace Jengine {
	namespace Input {

		Keyboard::Keyboard(GLFWwindow* window)
			: window(window) {
		}

		bool Keyboard::keyPressed(int key) {
			return glfwGetKey(this->window, key);
		}

		std::string Keyboard::keyName(int key) {
			return glfwGetKeyName(key, 0);
		}

	} // namespace Input
} // namespace Jengine
