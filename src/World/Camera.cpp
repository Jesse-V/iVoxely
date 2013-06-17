
#define GLM_SWIZZLE

#include "Camera.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <memory>
#include <sstream>


Camera::Camera()
{
	reset();
}



// Reset the camera back to its defaults
void Camera::reset()
{
	setPosition(glm::vec3(0.0, 0.0, 0.5));
	lookAt(glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0));

	fieldOfView   = 45.0f; // frustrum viewing apeture
	aspectRatio   = 4.0f/3.0f;
	nearFieldClip = 0.0001f;   // clip anything closer than this
	farFieldClip  = 100.0f; // clip anything farther than this
	projection    = glm::perspective(fieldOfView, aspectRatio, nearFieldClip, farFieldClip);
}



// Set the camera to an arbitrary location without changing orientation
void Camera::setPosition(const glm::vec3& pos)
{
	position = pos;
}



// Set the orientation of the camera without changing its position
void Camera::lookAt(const glm::vec3& newLookVector, const glm::vec3& newUpVector)
{
	lookDirection = newLookVector;
	upVector = newUpVector;
}



void Camera::translateX(float theta)
{
	translate(glm::vec3(theta, 0, 0));
}



void Camera::translateY(float theta)
{
	translate(glm::vec3(0, theta, 0));
}



void Camera::translateZ(float theta)
{
	translate(glm::vec3(0, 0, theta));
}



// Translate the camera along X/Y/Z
void Camera::translate(const glm::vec3& xyzTheta)
{
	glm::vec4 pos(position, 1.0);
	glm::vec4 look(lookDirection, 1.0);
	glm::mat4 matrix = glm::translate(glm::mat4(), xyzTheta);
	pos = matrix * pos;
	look = matrix * look;

	position = pos.xyz();
	lookDirection = look.xyz();
}



// Pitch the camera along the axis orthogonal to the up and look vectors
void Camera::pitch(float theta)
{
	glm::mat4 matrix = glm::rotate(glm::mat4(), theta, glm::cross(lookDirection, upVector));

	glm::vec4 look(lookDirection, 0.0);
	lookDirection = (matrix * look).xyz();

	glm::vec4 up(upVector, 0.0);
	upVector = (matrix * up).xyz();
}



// Yaw the camera along the up vector
void Camera::yaw(float theta)
{
	glm::mat4 matrix = glm::rotate(glm::mat4(), theta, upVector);

	glm::vec4 look(lookDirection, 0.0);
	lookDirection = (matrix * look).xyz();
}



// Roll the camera along the look axis
void Camera::roll(float theta)
{
	glm::mat4 matrix = glm::rotate(glm::mat4(), theta, lookDirection);

	glm::vec4 up(upVector, 0.0);
	upVector = (matrix * up).xyz();
}



// Sets the perspective of the camera
void Camera::setPerspective(float fieldOfViewDegrees, float aspectRatio, float nearclipdistance, float farclipdistance)
{
	this->fieldOfView   = fieldOfViewDegrees;
	this->aspectRatio   = aspectRatio;
	this->nearFieldClip = nearclipdistance;
	this->farFieldClip  = farclipdistance;
	this->projection = glm::perspective(fieldOfView, aspectRatio, nearFieldClip, farFieldClip);
}



void Camera::setFieldOfView(float degrees)
{
	fieldOfView = degrees;
	projection = glm::perspective(fieldOfView, aspectRatio, nearFieldClip, farFieldClip);
}



void Camera::setAspectRatio(float ratio)
{
	aspectRatio = ratio;
	projection = glm::perspective(fieldOfView, aspectRatio, nearFieldClip, farFieldClip);
}



void Camera::setNearFieldClipDistance(float distance)
{
	nearFieldClip = distance;
	projection = glm::perspective(fieldOfView, aspectRatio, nearFieldClip, farFieldClip);
}



void Camera::setFarFieldClipDistance(float distance)
{
	farFieldClip = distance;
	projection = glm::perspective(fieldOfView, aspectRatio, nearFieldClip, farFieldClip);
}



//accessors:

glm::vec3 Camera::getLookDirection()
{
	return lookDirection;
}



glm::vec3 Camera::getPosition()
{
	return position;
}



glm::vec3 Camera::getUpVector()
{
	return upVector;
}



float Camera::getFOV()
{
	return fieldOfView;
}



float Camera::getAspectRatio()
{
	return aspectRatio;
}



float Camera::getNearFieldClip()
{
	return nearFieldClip;
}



float Camera::getFarFieldClip()
{
	return farFieldClip;
}



glm::mat4 Camera::getProjectionMatrix()
{
	return projection;
}



std::string Camera::toString()
{
	std::stringstream ss;

	ss << "LookV: <" << lookDirection.x << ", " << lookDirection.y << ", " << lookDirection.z << "> ";
	ss << "UpV: <"   << upVector.x << ", " << upVector.y << ", " << upVector.z << "> ";
	ss << "Pos: <"   << position.x << ", " << position.y << ", " << position.z << ">";

	return ss.str();
}
