#ifndef GLOBJECT_H
#define GLOBJECT_H


namespace Jengine {

	class GLObject
	{
	public:
		GLObject();
		virtual ~GLObject();

		void bind();

	protected:

		inline virtual void onBind() = 0;

		unsigned int glId;
		static unsigned int currentlyBound;
	};

} // namespace Jengine

#endif // GLOBJECT_H
