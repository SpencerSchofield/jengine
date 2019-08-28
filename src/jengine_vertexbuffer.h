#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "jengine_globject.h"
#include "jengine_vertexattribute.h"
#include <vector>

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



	class VertexBuffer : public GLObject
	{
	public:
		VertexBuffer(const void* data, unsigned int size, unsigned int usage);
		~VertexBuffer() override;

		void addAttribute(unsigned int type, unsigned int count);

		VertexAttribute& operator[](int index);

		VertexAttribute& attribute(int index);

	private:

		void onBind() override;

		std::vector<VertexAttribute> attributes;
		unsigned int attributeOffset;

	};
}

#endif // VERTEXBUFFER_H
