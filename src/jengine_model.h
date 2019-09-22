#ifndef MODEL_H
#define MODEL_H

#include "jengine_vertexarray.h"

namespace Jengine {

	class Model
	{
	public:
		Model(VertexArray* vertexArray);

		static Model* loadOBJ(const std::string& fileName);

		const VertexArray* vertexArray;

	private:

	};

} // namespace Jengine

#endif // MODEL_H
