#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <GL/glew.h>
#include "jengine_vertexbuffer.h"
#include "jengine_vertexattribute.h"

namespace Jengine {

	class VertexArray
	{
	public:
		VertexArray(VertexBuffer* vertexBuffer);
		~VertexArray();

		void bind();

		VertexBuffer* const vertexBuffer;

	private:
		unsigned int glId;
		static unsigned int currentlyBound;
	};

} // namespace Jengine

#endif // VERTEXARRAY_H
