#include "jengine_vertexarray.h"

#include <GL/glew.h>

namespace Jengine {

	VertexArray::VertexArray(VertexBuffer* vertexBuffer)
		: vertexBuffer(vertexBuffer)
	{
		glGenVertexArrays(1, &this->glId);
		this->vertexBuffer->bind();
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &this->glId);
	}

	void VertexArray::onBind()
	{
		glBindVertexArray(this->glId);
	}

} // namespace Jengine
