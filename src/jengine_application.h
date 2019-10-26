#ifndef JENGINE_APPLICATION_H
#define JENGINE_APPLICATION_H

#include "jengine_renderer.h"
#include "input/jengine_input.h"

namespace Jengine {

	struct Application_Config {
		const char* name;
		int width;
		int height;
		bool vsync;
		bool continuousEvents;
		bool rawMotion;
		Jengine::Input::CURSOR_MODE cursorMode;
	};

	class Application {
	public:
		Application(
				Application_Config config);
		virtual ~Application();
		virtual void update(
				double deltaTime) = 0;
		double deltaTime() const;
		static inline Application& application()
		{
			return *latestApplication;
		}

		bool finished;
		Jengine::Renderer* renderer;
		Jengine::Input::Input* input;

		double prevTime {0};
		double currTime;

	private:
		static Application* latestApplication;
		Application_Config config;
	};
}

#endif // JENGINE_APPLICATION_H
