#ifndef VERTEXATTRIBUTE_H
#define VERTEXATTRIBUTE_H

namespace Jengine {

	enum ATTRIBUTE_TYPE {
		BYTE = 0x1400,
		UNSIGNED_BYTE = 0x1401,
		SHORT = 0x1402,
		UNSIGNED_SHORT = 0x1403,
		INT = 0x1404,
		UNSIGNED_INT = 0x1405,
		FLOAT = 0x1406,
		TWO_BYTES = 0x1407,
		THREE_BYTES = 0x1408,
		FOUR_BYTES = 0x1409,
		DOUBLE = 0x140A
	};

	class VertexAttribute
	{
	public:
		VertexAttribute(
				unsigned int index,
				unsigned int type,
				unsigned int count,
				unsigned int offset,
				unsigned int* const size = nullptr);
		void enable();
		void disable();
		void createAttribute(
				unsigned int stride) const;

	private:
		bool enabled;
		unsigned int index;
		unsigned int count;
		unsigned int type;
		unsigned int offset;
	};
}

#endif // VERTEXATTRIBUTE_H
