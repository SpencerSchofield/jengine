#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <GL/glew.h>
#include "jengine_globject.h"
#include "jengine_vertexbuffer.h"
#include "jengine_vertexattribute.h"

namespace Jengine {

	class VertexArray : public GLObject
	{
	public:
		VertexArray(VertexBuffer* vertexBuffer);
		~VertexArray() override;

		VertexBuffer* const vertexBuffer;

	private:
		void onBind() override;
	};

} // namespace Jengine

#endif // VERTEXARRAY_H
