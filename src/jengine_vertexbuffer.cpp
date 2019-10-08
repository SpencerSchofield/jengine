#include "jengine_vertexbuffer.h"

#include <GL/glew.h>

namespace Jengine {

	VertexBuffer::VertexBuffer(const void* data, unsigned long size, unsigned int usage)
	{
		glGenBuffers(1, &this->glId);
		glBindBuffer(GL_ARRAY_BUFFER, this->glId);
		glBufferData(GL_ARRAY_BUFFER, size, data, usage);
		//glCreateBuffers(1, &this->glId);
		//glNamedBufferStorage(this->glId, size, data, 0);
	}

	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(1, &this->glId);
	}

	void VertexBuffer::addAttribute(unsigned int type, unsigned int count) {
		unsigned int size;
		this->attributes.emplace_back(
					VertexAttribute(static_cast<unsigned int>(this->attributes.size()),
									type, count, this->attributeOffset, &size));
		this->attributeOffset += size;
	}


	VertexAttribute& VertexBuffer::operator[](unsigned long index) {
		return this->attributes[index];
	}

	VertexAttribute& VertexBuffer::attribute(unsigned long index) {
		return this->attributes[index];
	}

	void VertexBuffer::bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, this->glId);
	}

	void VertexBuffer::createAttributes() {
		for (unsigned int i = 0; i < this->attributes.size(); i++) {
			this->attributes[i].createAttribute(attributeOffset);
		}
	}

	unsigned int VertexBuffer::getId() {
		return this->glId;
	}
}

