#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <GL/glew.h>
#include "jengine_globject.h"
#include "jengine_vertexbuffer.h"
#include "jengine_vertexattribute.h"
#include "jengine_indexbuffer.h"
#include "jengine_shader.h"

namespace Jengine {

	class VertexArray : public GLObject
	{
	public:
		VertexArray(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, Shader* shader);
		~VertexArray() override;

		VertexBuffer* const vertexBuffer;
		IndexBuffer* const indexBuffer;
		Shader* const shader;

	private:
		void onBind() override;
	};

} // namespace Jengine

#endif // VERTEXARRAY_H
