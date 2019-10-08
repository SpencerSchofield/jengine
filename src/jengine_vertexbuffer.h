#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

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



	class VertexBuffer
	{
	public:
		VertexBuffer(const void* data, unsigned long size, unsigned int usage);
		~VertexBuffer();

		void addAttribute(unsigned int type, unsigned int count);

		VertexAttribute& operator[](unsigned long index);

		VertexAttribute& attribute(unsigned long index);

		void createAttributes();

		unsigned int getId();

		void bind() const;

	private:

		unsigned int glId;

		std::vector<VertexAttribute> attributes;
		unsigned int attributeOffset {0};

	};
}

#endif // VERTEXBUFFER_H
