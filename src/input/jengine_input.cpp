#include "../pch.h"
#include "jengine_input.h"

namespace Jengine {
	namespace Input {

		Input::Input(GLFWwindow* window, void (*f)(void))
			: Keyboard(window), Mouse(window), inputFunc(f) {
		}

		void Input::getEvents() const {
			(*inputFunc)();
		}

	} // namespace Input
} // namespace Jengine
