#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <GLFW/glfw3.h>
#include <string>

#define 	JENGINE_KEY_UNKNOWN   -1
#define 	JENGINE_KEY_SPACE   32
#define 	JENGINE_KEY_APOSTROPHE   39 /* ' */
#define 	JENGINE_KEY_COMMA   44 /* , */
#define 	JENGINE_KEY_MINUS   45 /* - */
#define 	JENGINE_KEY_PERIOD   46 /* . */
#define 	JENGINE_KEY_SLASH   47 /* / */
#define 	JENGINE_KEY_0   48
#define 	JENGINE_KEY_1   49
#define 	JENGINE_KEY_2   50
#define 	JENGINE_KEY_3   51
#define 	JENGINE_KEY_4   52
#define 	JENGINE_KEY_5   53
#define 	JENGINE_KEY_6   54
#define 	JENGINE_KEY_7   55
#define 	JENGINE_KEY_8   56
#define 	JENGINE_KEY_9   57
#define 	JENGINE_KEY_SEMICOLON   59 /* ; */
#define 	JENGINE_KEY_EQUAL   61 /* = */
#define 	JENGINE_KEY_A   65
#define 	JENGINE_KEY_B   66
#define 	JENGINE_KEY_C   67
#define 	JENGINE_KEY_D   68
#define 	JENGINE_KEY_E   69
#define 	JENGINE_KEY_F   70
#define 	JENGINE_KEY_G   71
#define 	JENGINE_KEY_H   72
#define 	JENGINE_KEY_I   73
#define 	JENGINE_KEY_J   74
#define 	JENGINE_KEY_K   75
#define 	JENGINE_KEY_L   76
#define 	JENGINE_KEY_M   77
#define 	JENGINE_KEY_N   78
#define 	JENGINE_KEY_O   79
#define 	JENGINE_KEY_P   80
#define 	JENGINE_KEY_Q   81
#define 	JENGINE_KEY_R   82
#define 	JENGINE_KEY_S   83
#define 	JENGINE_KEY_T   84
#define 	JENGINE_KEY_U   85
#define 	JENGINE_KEY_V   86
#define 	JENGINE_KEY_W   87
#define 	JENGINE_KEY_X   88
#define 	JENGINE_KEY_Y   89
#define 	JENGINE_KEY_Z   90
#define 	JENGINE_KEY_LEFT_BRACKET   91 /* [ */
#define 	JENGINE_KEY_BACKSLASH   92 /* \ */
#define 	JENGINE_KEY_RIGHT_BRACKET   93 /* ] */
#define 	JENGINE_KEY_GRAVE_ACCENT   96 /* ` */
#define 	JENGINE_KEY_WORLD_1   161 /* non-US #1 */
#define 	JENGINE_KEY_WORLD_2   162 /* non-US #2 */
#define 	JENGINE_KEY_ESCAPE   256
#define 	JENGINE_KEY_ENTER   257
#define 	JENGINE_KEY_TAB   258
#define 	JENGINE_KEY_BACKSPACE   259
#define 	JENGINE_KEY_INSERT   260
#define 	JENGINE_KEY_DELETE   261
#define 	JENGINE_KEY_RIGHT   262
#define 	JENGINE_KEY_LEFT   263
#define 	JENGINE_KEY_DOWN   264
#define 	JENGINE_KEY_UP   265
#define 	JENGINE_KEY_PAGE_UP   266
#define 	JENGINE_KEY_PAGE_DOWN   267
#define 	JENGINE_KEY_HOME   268
#define 	JENGINE_KEY_END   269
#define 	JENGINE_KEY_CAPS_LOCK   280
#define 	JENGINE_KEY_SCROLL_LOCK   281
#define 	JENGINE_KEY_NUM_LOCK   282
#define 	JENGINE_KEY_PRINT_SCREEN   283
#define 	JENGINE_KEY_PAUSE   284
#define 	JENGINE_KEY_F1   290
#define 	JENGINE_KEY_F2   291
#define 	JENGINE_KEY_F3   292
#define 	JENGINE_KEY_F4   293
#define 	JENGINE_KEY_F5   294
#define 	JENGINE_KEY_F6   295
#define 	JENGINE_KEY_F7   296
#define 	JENGINE_KEY_F8   297
#define 	JENGINE_KEY_F9   298
#define 	JENGINE_KEY_F10   299
#define 	JENGINE_KEY_F11   300
#define 	JENGINE_KEY_F12   301
#define 	JENGINE_KEY_F13   302
#define 	JENGINE_KEY_F14   303
#define 	JENGINE_KEY_F15   304
#define 	JENGINE_KEY_F16   305
#define 	JENGINE_KEY_F17   306
#define 	JENGINE_KEY_F18   307
#define 	JENGINE_KEY_F19   308
#define 	JENGINE_KEY_F20   309
#define 	JENGINE_KEY_F21   310
#define 	JENGINE_KEY_F22   311
#define 	JENGINE_KEY_F23   312
#define 	JENGINE_KEY_F24   313
#define 	JENGINE_KEY_F25   314
#define 	JENGINE_KEY_KP_0   320
#define 	JENGINE_KEY_KP_1   321
#define 	JENGINE_KEY_KP_2   322
#define 	JENGINE_KEY_KP_3   323
#define 	JENGINE_KEY_KP_4   324
#define 	JENGINE_KEY_KP_5   325
#define 	JENGINE_KEY_KP_6   326
#define 	JENGINE_KEY_KP_7   327
#define 	JENGINE_KEY_KP_8   328
#define 	JENGINE_KEY_KP_9   329
#define 	JENGINE_KEY_KP_DECIMAL   330
#define 	JENGINE_KEY_KP_DIVIDE   331
#define 	JENGINE_KEY_KP_MULTIPLY   332
#define 	JENGINE_KEY_KP_SUBTRACT   333
#define 	JENGINE_KEY_KP_ADD   334
#define 	JENGINE_KEY_KP_ENTER   335
#define 	JENGINE_KEY_KP_EQUAL   336
#define 	JENGINE_KEY_LEFT_SHIFT   340
#define 	JENGINE_KEY_LEFT_CONTROL   341
#define 	JENGINE_KEY_LEFT_ALT   342
#define 	JENGINE_KEY_LEFT_SUPER   343
#define 	JENGINE_KEY_RIGHT_SHIFT   344
#define 	JENGINE_KEY_RIGHT_CONTROL   345
#define 	JENGINE_KEY_RIGHT_ALT   346
#define 	JENGINE_KEY_RIGHT_SUPER   347
#define 	JENGINE_KEY_MENU   348
#define 	JENGINE_KEY_LAST   JENGINE_KEY_MENU

namespace Jengine {
	namespace Input {

		class Keyboard
		{
		public:
			Keyboard(GLFWwindow* window);

			bool keyPressed(int key) const;
			std::string keyName(int key) const;

		private:
			GLFWwindow* window;
		};

	} // namespace Input
} // namespace Jengine

#endif // KEYBOARD_H
