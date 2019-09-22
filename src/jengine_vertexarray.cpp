#include "jengine_vertexarray.h"

#include <GL/glew.h>

namespace Jengine {

	VertexArray::VertexArray(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer)
		: vertexBuffer(vertexBuffer), indexBuffer(indexBuffer)
	{
		glGenVertexArrays(1, &this->glId);
		glBindVertexArray(this->glId);
		this->vertexBuffer->bind();
		this->indexBuffer->bind();
	}

	VertexArray::~VertexArray() {
		glDeleteVertexArrays(1, &this->glId);
	}

	void VertexArray::bind() {
		glBindVertexArray(this->glId);
		this->vertexBuffer->bind();
		this->indexBuffer->bind();
	}

} // namespace Jengine
