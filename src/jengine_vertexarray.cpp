#include "jengine_vertexarray.h"

#include <GL/glew.h>
#include "jengine_logging.h"

namespace Jengine {

	VertexArray::VertexArray(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer)
		: vertexBuffer(vertexBuffer), indexBuffer(indexBuffer)
	{
		glCreateVertexArrays(1, &this->glId);
		glBindVertexArray(this->glId);
		this->vertexBuffer->bind();
		this->indexBuffer->bind();

	}

	VertexArray::VertexArray(UNIMPLEMENTED const void* data, UNIMPLEMENTED unsigned long size, UNIMPLEMENTED unsigned int usage)
		: vertexBuffer(nullptr), indexBuffer(nullptr) {
		//glCreateVertexArrays(1, &this->glId);
		//glCreateBuffers(2, this->buffer);
		//glNamedBufferStorage(this->buffer[0], size, data, 0);
		//glVertexArrayVertexBuffer(this->glId, 0, this->buffer[0], 0, sizeof(float) * 3);
	}

	VertexArray::~VertexArray() {
		glDeleteVertexArrays(1, &this->glId);
	}

	void VertexArray::bind() const {
		//JENGINE_TRACE("");
		glBindVertexArray(this->glId);
		this->vertexBuffer->bind();
		this->indexBuffer->bind();
	}

} // namespace Jengine
