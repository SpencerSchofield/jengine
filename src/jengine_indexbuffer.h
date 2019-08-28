#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include "jengine_globject.h"

namespace Jengine {

	class IndexBuffer : public GLObject
	{
	public:
		IndexBuffer();

	private:
		void onBind() override;
	};

} // namespace Jengine

#endif // INDEXBUFFER_H
