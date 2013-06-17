
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm/glm.hpp"
#include <memory>
#include <string>

class Camera
{
	public:
		Camera();
		void reset();
		void render();

		// Functions to move/direct the camera
		void setPosition(const glm::vec3& pos);
		void lookAt(const glm::vec3& look, const glm::vec3& up = glm::vec3(0.0, 1.0, 0.0));

		void translateX(float theta);
		void translateY(float theta);
		void translateZ(float theta);
		void translate(const glm::vec3& xyzTheta);

		void roll(float theta);
		void pitch(float theta);
		void yaw(float theta);

		// Set the perspective of the camera and its clipping distances
		void setPerspective(float fieldOfViewDegrees, float aspectRatio, float nearclip, float farclip);

		void setFieldOfView(float degrees);
		void setAspectRatio(float ratio);
		void setNearFieldClipDistance(float distance);
		void setFarFieldClipDistance(float distance);

		glm::vec3 getLookDirection();
		glm::vec3 getPosition();
		glm::vec3 getUpVector();

		float getFOV();
		float getAspectRatio();
		float getNearFieldClip();
		float getFarFieldClip();

		glm::mat4 getProjectionMatrix();
		std::string toString();

	private:
		glm::vec3 lookDirection, position, upVector;
		float fieldOfView, aspectRatio, nearFieldClip, farFieldClip;
		glm::mat4 projection;
};

#endif
