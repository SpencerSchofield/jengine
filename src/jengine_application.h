#ifndef JENGINE_APPLICATION_H
#define JENGINE_APPLICATION_H

namespace Jengine {
	class Application {
	public:
		Application() {latestApplication = this;}
		virtual ~Application() {}

		virtual bool onStartup() {}
		virtual bool onShutdown() {}
		virtual bool update() {}
		virtual bool draw() {}

		static Application& application() {return *latestApplication;}
		bool finished;

	private:
		inline static Application* latestApplication;
	};
}

#endif // JENGINE_APPLICATION_H
