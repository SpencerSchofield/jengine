#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

namespace Jengine {

	class Camera
	{
	public:
		Camera(double fov, double width, double height, double near, double far);
		Camera(double left, double right, double bottom, double top, double near, double far);

		glm::mat4 getViewMatrix();
		void setPosition(glm::vec3 position);
		void setAngle(glm::vec3 angle);
		void setPositionAndAngle(glm::mat4 matrix);

		void modifyPosition(glm::vec3 position);
		void modifyAngle(glm::vec3 angle);
		void modifyPositionAndAngle(glm::mat4 matrix);

	private:

		glm::mat4 projection;
		glm::mat4 position;
		glm::mat4 view;
		bool updated;
	};

} // namespace Jengine

#endif // CAMERA_H
