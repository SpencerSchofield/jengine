#ifndef JENGINE_APPLICATION_H
#define JENGINE_APPLICATION_H

#include "jengine_renderer.h"

namespace Jengine {
	class Application {
	public:
		Application(const char* name, int width, int height);
		virtual ~Application();

		virtual bool onStartup() {return true;}
		virtual bool onShutdown() {return true;}
		virtual bool update() {return true;}
		virtual bool draw() {return true;}

		static Application& application() {return *latestApplication;}
		bool finished;
		Jengine::Renderer* renderer;

	private:
		inline static Application* latestApplication;
	};
}

#endif // JENGINE_APPLICATION_H
