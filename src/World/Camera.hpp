
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm/glm.hpp"
#include <GL/glew.h>
#include <memory>
#include <string>

class Camera
{
	public:
		Camera();
		void reset();
		void sync(GLuint handle) const;

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

		glm::vec3 getLookDirection()  const;
		glm::vec3 getPosition()  const;
		glm::vec3 getUpVector()  const;

		float getFOV() const;
		float getAspectRatio() const;
		float getNearFieldClip() const;
		float getFarFieldClip() const;

		glm::mat4 getProjectionMatrix() const;
		std::string toString() const;

	private:
		glm::vec3 lookDirection, position, upVector;
		float fieldOfView, aspectRatio, nearFieldClip, farFieldClip;
		glm::mat4 projection;
};

#endif
