#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

namespace Jengine {

	class IndexBuffer
	{
	public:
		IndexBuffer(
				const unsigned int* data,
				unsigned long count);
		unsigned long getCount() const;
		void bind() const;

	private:
		unsigned int glId;
		unsigned long count;
	};

} // namespace Jengine

#endif // INDEXBUFFER_H
