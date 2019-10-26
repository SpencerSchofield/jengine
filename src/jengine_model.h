#ifndef MODEL_H
#define MODEL_H

#include "jengine_vertexarray.h"

namespace Jengine {

	class Model
	{
	public:
		Model(
				VertexArray* vertexArray);
		virtual ~Model();
		static Model* loadOBJ(
				const std::string& fileName);
		void enable() const;

		VertexArray* const vertexArray;

	private:

	};

} // namespace Jengine

#endif // MODEL_H
