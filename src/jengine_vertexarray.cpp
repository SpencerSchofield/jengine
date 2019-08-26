#include "jengine_vertexarray.h"

#include <GL/glew.h>

namespace Jengine {

	unsigned int VertexArray::currentlyBound = 0;

	VertexArray::VertexArray(VertexBuffer* vertexBuffer)
		: vertexBuffer(vertexBuffer)
	{
		glGenVertexArrays(1, &this->glId);
		this->vertexBuffer->bind();
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &this->glId);
		if (this->glId == currentlyBound)
			currentlyBound = 0;
	}

	void VertexArray::bind()
	{
		if (this->glId == currentlyBound)
			return;
		glBindVertexArray(this->glId);
		currentlyBound = this->glId;
	}

} // namespace Jengine
