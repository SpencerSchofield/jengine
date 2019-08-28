#include "jengine_globject.h"

namespace Jengine {

	unsigned int GLObject::currentlyBound = 0;

	GLObject::GLObject()
	{
		currentlyBound = this->glId;
	}

	GLObject::~GLObject()
	{
		if (this->glId == currentlyBound)
			currentlyBound = 0;
	}

	void GLObject::bind()
	{
		if (this->glId == currentlyBound)
			return;
		onBind();
		currentlyBound = this->glId;
	}

} // namespace Jengine
