
#include "Camera.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <memory>
#include <sstream>
#include <stdexcept>
#include <iostream>


//http://stackoverflow.com/questions/12138721/rotating-a-open-gl-camera-correctly-using-glm

Camera::Camera()
{
    reset();
}



// Reset the camera back to its defaults
void Camera::reset()
{
    setPosition(glm::vec3(0.0, 0.0, 0.5));
    lookAt(glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0));

    fieldOfView_   = 45.0f;         // frustrum viewing aperture
    aspectRatio_   = 4.0f / 3.0f;   // frustrum view angling
    nearFieldClip_ = 0.005f;        // clip anything closer than this
    farFieldClip_  = 30.0f;         // clip anything farther than this
    updateProjectionMatrix();
}



void Camera::sync(GLuint programHandle) const
{
    //assemble view matrix and sync with program handle
    GLint viewMatrixUniform = glGetUniformLocation(programHandle, "viewMatrix");
    glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE,
                       glm::value_ptr(getViewMatrix()));

    //sync projection matrix with program handle
    GLint projMatrixUniform = glGetUniformLocation(programHandle, "projMatrix");
    glUniformMatrix4fv(projMatrixUniform, 1, GL_FALSE,
                       glm::value_ptr(getProjectionMatrix()));

    //assert that they went through to GLSL variables
    if (viewMatrixUniform < 0 || projMatrixUniform < 0)
        throw std::runtime_error("Unable to find Camera uniform variables!");
}



// Set the camera to an arbitrary location without changing orientation
void Camera::setPosition(const glm::vec3& newPosition)
{
    if (newPosition == lookingAt_)
        throw std::runtime_error("Cannot be where we're looking at!");

    position_ = newPosition;
}



// Set the orientation of the camera without changing its position_
void Camera::lookAt(const glm::vec3& newLookVector, const glm::vec3& newUpVector)
{
    if (newLookVector == position_)
        throw std::runtime_error("Cannot look at same point as position!");

    lookingAt_ = newLookVector;
    upVector_ = newUpVector;
}



void Camera::translateX(float magnitude)
{
    translate(glm::vec3(magnitude, 0, 0));
}



void Camera::translateY(float magnitude)
{
    translate(glm::vec3(0, magnitude, 0));
}



void Camera::translateZ(float magnitude)
{
    translate(glm::vec3(0, 0, magnitude));
}



//translate the camera along X/Y/Z
void Camera::translate(const glm::vec3& delta)
{
    /*
    glm::mat4 magMatrix = glm::translate(glm::mat4(), delta);
    position_  = (magMatrix * glm::vec4(position_,      1)).xyz();
    lookingAt_ = (magMatrix * glm::vec4(lookingAt_, 1)).xyz();
    */

    position_ += delta;
    lookingAt_ += delta;
}



void Camera::moveForward(float magnitude)
{
    glm::vec3 orientation = glm::normalize(lookingAt_ - position_);
    translate(orientation * magnitude);
}



void Camera::moveRight(float magnitude)
{
    glm::vec3 orientation = glm::normalize(lookingAt_ - position_);
    glm::vec3 vec = glm::normalize(glm::cross(orientation, upVector_));
    translate(vec * magnitude);
}



void Camera::moveUp(float magnitude)
{
    translate(glm::normalize(upVector_) * magnitude);
}



// Pitch the camera along the axis orthogonal to the up and look vectors
void Camera::pitch(float theta)
{
    glm::mat4 matrix = glm::rotate(glm::mat4(), theta,
                                   glm::cross(lookingAt_, upVector_));

    glm::vec4 look(lookingAt_, 0.0);
    lookingAt_ = (matrix * look).xyz();

    glm::vec4 up(upVector_, 0.0);
    upVector_ = (matrix * up).xyz();
}



// Yaw the camera along the up vector
void Camera::yaw(float theta)
{
    glm::mat4 matrix = glm::rotate(glm::mat4(), theta, upVector_);

    glm::vec4 look(lookingAt_, 0.0);
    lookingAt_ = (matrix * look).xyz();
}



// Roll the camera along the look axis
void Camera::roll(float theta)
{
    glm::mat4 matrix = glm::rotate(glm::mat4(), theta, lookingAt_);

    glm::vec4 up(upVector_, 0.0);
    upVector_ = (matrix * up).xyz();
}



void Camera::setFieldOfView(float degrees)
{
    fieldOfView_ = degrees;
    updateProjectionMatrix();
}



void Camera::setAspectRatio(float ratio)
{
    aspectRatio_ = ratio;
    updateProjectionMatrix();
}



void Camera::setNearFieldClipDistance(float distance)
{
    nearFieldClip_ = distance;
    updateProjectionMatrix();
}



void Camera::setFarFieldClipDistance(float distance)
{
    farFieldClip_ = distance;
    updateProjectionMatrix();
}



// Sets the perspective of the camera
void Camera::setPerspective(
    float fieldOfViewDegrees, float aspectRatio,
    float nearClipDistance, float farClipDistance
)
{
    aspectRatio_   = aspectRatio;
    nearFieldClip_ = nearClipDistance;
    farFieldClip_  = farClipDistance;
    setFieldOfView(fieldOfViewDegrees);
}



void Camera::updateProjectionMatrix()
{
    projection_ = glm::perspective(fieldOfView_, aspectRatio_,
                                  nearFieldClip_, farFieldClip_);
}



//accessors:

glm::vec3 Camera::getPosition() const
{
    return position_;
}



glm::vec3 Camera::getLookingAt() const
{
    return lookingAt_;
}



glm::vec3 Camera::getUpVector() const
{
    return upVector_;
}



glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(getPosition(), getLookingAt(), getUpVector());
}



float Camera::getFOV() const
{
    return fieldOfView_;
}



float Camera::getAspectRatio() const
{
    return aspectRatio_;
}



float Camera::getNearFieldClip() const
{
    return nearFieldClip_;
}



float Camera::getFarFieldClip() const
{
    return farFieldClip_;
}



glm::mat4 Camera::getProjectionMatrix() const
{
    return projection_;
}



std::string Camera::toString() const
{
    std::stringstream ss;

    ss << "Look@: <" << lookingAt_.x << ", " << lookingAt_.y <<
                    ", " << lookingAt_.z << "> ";
    ss << "UpV: <"   << upVector_.x << ", " << upVector_.y <<
                    ", " << upVector_.z << "> ";
    ss << "Pos: <"   << position_.x << ", " << position_.y <<
                    ", " << position_.z << ">";

    return ss.str();
}
