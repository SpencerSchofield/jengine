#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

namespace Jengine {

	enum USE {
		STREAM_DRAW  = 0x88E0,
		STREAM_READ  = 0x88E1,
		STREAM_COPY  = 0x88E2,
		STATIC_DRAW  = 0x88E4,
		STATIC_READ  = 0x88E5,
		STATIC_COPY  = 0x88E6,
		DYNAMIC_DRAW = 0x88E8,
		DYNAMIC_READ = 0x88E9,
		DYNAMIC_COPY = 0x88EA
	};



	class VertexBuffer
	{
	public:
		VertexBuffer(const void* data, unsigned int size, unsigned int usage);
		~VertexBuffer();

		void bind();

	private:
		unsigned int glId;
		static unsigned int currentlybound;

	};
}

#endif // VERTEXBUFFER_H
