#include "jengine_vertexbuffer.h"

#include <GL/glew.h>

namespace Jengine {
	unsigned int VertexBuffer::currentlybound = 0;

	VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int usage)
	{
		glGenBuffers(1, &this->glId);
		glBindBuffer(GL_ARRAY_BUFFER, this->glId);
		currentlybound = this->glId;
		glBufferData(GL_ARRAY_BUFFER, size, data, usage);
		this->attributeOffset = 0;
	}

	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(1, &this->glId);
		if (this->glId == currentlybound)
			currentlybound = 0;
	}

	void VertexBuffer::bind()
	{
		if (this->glId == currentlybound)
			return;
		glBindBuffer(GL_ARRAY_BUFFER, this->glId);
		currentlybound = this->glId;
	}

	void VertexBuffer::addAttribute(unsigned int type, unsigned int count) {
		unsigned int size;
		this->attributes.emplace_back(VertexAttribute(this->attributes.size(), type, count, this->attributeOffset, &size));
		this->attributeOffset += size;
	}


	VertexAttribute& VertexBuffer::operator[](int index){
		return this->attributes[index];
	}

	VertexAttribute& VertexBuffer::attribute(int index) {
		return this->attributes[index];
	}

}

