#ifndef MOUSE_H
#define MOUSE_H

#include <GLFW/glfw3.h>

#define JENGINE_MOUSE_BUTTON_1   0
#define JENGINE_MOUSE_BUTTON_2   1
#define JENGINE_MOUSE_BUTTON_3   2
#define JENGINE_MOUSE_BUTTON_4   3
#define JENGINE_MOUSE_BUTTON_5   4
#define JENGINE_MOUSE_BUTTON_6   5
#define JENGINE_MOUSE_BUTTON_7   6
#define JENGINE_MOUSE_BUTTON_8   7
#define JENGINE_MOUSE_BUTTON_LAST   JENGINE_MOUSE_BUTTON_8
#define JENGINE_MOUSE_BUTTON_LEFT   JENGINE_MOUSE_BUTTON_1
#define JENGINE_MOUSE_BUTTON_RIGHT   JENGINE_MOUSE_BUTTON_2
#define JENGINE_MOUSE_BUTTON_MIDDLE   JENGINE_MOUSE_BUTTON_3


namespace Jengine {
	namespace Input {

		struct MousePosition {
			double x;
			double y;
		};

		enum class CURSOR_MODE {
			DISABLED = GLFW_CURSOR_DISABLED,
			HIDDEN = GLFW_CURSOR_HIDDEN,
			NORMAL = GLFW_CURSOR_NORMAL
		};

		class Mouse {
		public:
			Mouse(GLFWwindow* window);
			void setCursorMode(CURSOR_MODE mode);
			void setRawMotion(bool raw);
			MousePosition getMousePosition();
			MousePosition getRelativeMousePosition();
			bool mouseButtonClicked(int button);
			// Only works with vertical scroll currently
			double getMouseScroll();

		private:
			static void scrollCallback(GLFWwindow* window, double xoff, double yoff);
			GLFWwindow* window;
			MousePosition oPosition {0, 0};
			inline static double xScrollRel {0};
			inline static GLFWwindow* windowScroll;
		};

	} // namespace Input
} // namespace Jengine

#endif // MOUSE_H
