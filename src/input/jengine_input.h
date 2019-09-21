#ifndef INPUT_H
#define INPUT_H

#include "jengine_keyboard.h"
#include "jengine_mouse.h"

namespace Jengine {
	namespace Input {

		class Input : public Keyboard, public Mouse {
		public:
			Input(GLFWwindow* window, void (*f)(void));

			void getEvents();

		private:
			void (*inputFunc)(void);
		};

	} // namespace Input
} // namespace Jengine

#endif // INPUT_H
