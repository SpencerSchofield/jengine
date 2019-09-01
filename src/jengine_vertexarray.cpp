#include "jengine_vertexarray.h"

#include <GL/glew.h>

namespace Jengine {

	VertexArray::VertexArray(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, Shader* shader)
		: vertexBuffer(vertexBuffer), indexBuffer(indexBuffer), shader(shader)
	{
		glGenVertexArrays(1, &this->glId);
		glBindVertexArray(this->glId);
		VertexBuffer::currentlyBound = 0;
		IndexBuffer::currentlyBound = 0;
		Shader::currentlyBound = 0;
		this->vertexBuffer->bind();
		this->indexBuffer->bind();
		this->shader->bind();
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &this->glId);
	}

	void VertexArray::onBind()
	{
		glBindVertexArray(this->glId);
		this->vertexBuffer->bind();
		this->indexBuffer->bind();
		this->shader->bind();
	}

} // namespace Jengine
