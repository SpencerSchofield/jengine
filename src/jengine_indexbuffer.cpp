#include "jengine_indexbuffer.h"

#include <GL/glew.h>

namespace Jengine {

	IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	{
		glGenBuffers(1, &this->glId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->glId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW);
		this->count = count;
	}

	unsigned int IndexBuffer::getCount()
	{
		return this->count;
	}

	void IndexBuffer::onBind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->glId);
	}

} // namespace Jengine
