#include "jengine_vertexattribute.h"

#include <GL/glew.h>

namespace Jengine {

	VertexAttribute::VertexAttribute(unsigned int index, unsigned int type, unsigned int count, unsigned int offset, unsigned int* const size)
	{
		unsigned int sizes[] = {1,1,sizeof(short),sizeof(short),
								sizeof(int),sizeof(int),sizeof(float),
							   2,3,4,sizeof(double)};
		unsigned int typeSize = sizes[type-Jengine::ATTRIBUTE_TYPE::BYTE];
		glVertexAttribPointer(index, count, type, GL_FALSE, typeSize*count, (const void*) offset);
		if (size)
			*size = typeSize*count;
	}

	void VertexAttribute::enable() {
		if (this->enabled)
			return;
		glEnableVertexAttribArray(this->index);
		this->enabled = true;
	}

	void VertexAttribute::disable() {
		if (!this->enabled)
			return;
		glDisableVertexAttribArray(this->index);
		this->enabled = false;
	}

}
