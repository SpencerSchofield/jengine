#include "jengine_vertexbuffer.h"

#include <GL/glew.h>

unsigned int Jengine::VertexBuffer::currentlybound = 0;

Jengine::VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int usage)
{
	glGenBuffers(1, &this->glId);
	glBindBuffer(GL_ARRAY_BUFFER, this->glId);
	currentlybound = this->glId;
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

Jengine::VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &this->glId);
	if (this->glId == currentlybound)
		currentlybound = 0;
}

void Jengine::VertexBuffer::bind()
{
	if (this->glId == currentlybound)
		return;
	glBindBuffer(GL_ARRAY_BUFFER, this->glId);
	currentlybound = this->glId;
}
