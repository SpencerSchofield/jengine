#include "jengine_indexbuffer.h"

#include <GL/glew.h>

namespace Jengine {

	IndexBuffer::IndexBuffer(const unsigned int* data, unsigned long count)
		: count(count) {
		glGenBuffers(1, &this->glId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->glId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW);
	}

	unsigned long IndexBuffer::getCount() const {
		return this->count;
	}

	void IndexBuffer::bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->glId);
	}

} // namespace Jengine
