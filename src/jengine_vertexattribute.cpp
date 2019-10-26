#include "jengine_vertexattribute.h"

#include <GL/glew.h>

namespace Jengine {

	VertexAttribute::VertexAttribute(
			unsigned int index,
			unsigned int type,
			unsigned int count,
			unsigned int offset,
			unsigned int* const size)
	{
		unsigned int sizes[] = {1,1,sizeof(short),sizeof(short),
								sizeof(int),sizeof(int),sizeof(float),
							   2,3,4,sizeof(double)};
		unsigned int typeSize = sizes[type-Jengine::ATTRIBUTE_TYPE::BYTE];

		if (size)
			*size = typeSize*count;
		this->enabled = false;
		this->index = index;
		this->count = count;
		this->type = type;
		this->offset = offset;
	}

	void VertexAttribute::enable()
	{
		if (this->enabled)
			return;
		glEnableVertexAttribArray(this->index);
		this->enabled = true;
	}

	void VertexAttribute::disable()
	{
		if (!this->enabled)
			return;
		glDisableVertexAttribArray(this->index);
		this->enabled = false;
	}


	void VertexAttribute::createAttribute(
			unsigned int stride) const
	{
		glVertexAttribPointer(this->index, this->count, this->type,
			GL_FALSE, stride, reinterpret_cast<const void*>(this->offset));
	}
}
