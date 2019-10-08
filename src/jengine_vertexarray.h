#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <GL/glew.h>
#include "jengine_vertexbuffer.h"
#include "jengine_vertexattribute.h"
#include "jengine_indexbuffer.h"

namespace Jengine {

	class VertexArray
	{
	public:
		VertexArray(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer);
		VertexArray(const void* data, unsigned long size, unsigned int usage);
		~VertexArray();

		VertexBuffer* const vertexBuffer;
		IndexBuffer* const indexBuffer;

		void bind() const;

	private:
		unsigned int glId;
		unsigned int buffer[2];
	};

} // namespace Jengine

#endif // VERTEXARRAY_H
