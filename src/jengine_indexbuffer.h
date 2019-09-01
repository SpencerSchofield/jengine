#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include "jengine_globject.h"

namespace Jengine {

	class IndexBuffer : public GLObject
	{
	public:
		IndexBuffer(const unsigned int* data, unsigned int count);

		unsigned int getCount();

	private:
		void onBind() override;
		unsigned int count;
	};

} // namespace Jengine

#endif // INDEXBUFFER_H
