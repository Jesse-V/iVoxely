
#define GLM_SWIZZLE

#include "Camera.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <memory>
#include <sstream>
#include <stdexcept>

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

    fieldOfView_   = 45.0f; // frustrum viewing apeture
    aspectRatio_   = 4.0f/3.0f;
    nearFieldClip_ = 0.0001f;   // clip anything closer than this
    farFieldClip_  = 100.0f; // clip anything farther than this
    projection_    = glm::perspective(fieldOfView_, aspectRatio_,
                                     nearFieldClip_, farFieldClip_);
}



void Camera::sync(GLuint handle) const
{
    GLint viewMatrixUniform = glGetUniformLocation(handle, "viewMatrix");
    glm::mat4 viewMatrix = glm::lookAt(
        getPosition(), getLookDirection(), getUpVector());
    glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE,
                       glm::value_ptr(viewMatrix));

    GLint projMatrixUniform = glGetUniformLocation(handle, "projMatrix");
    glUniformMatrix4fv(projMatrixUniform, 1, GL_FALSE,
                       glm::value_ptr(getProjectionMatrix()));

    if (viewMatrixUniform < 0 || projMatrixUniform < 0)
        throw std::runtime_error("Unable to find Camera uniform variables!");
}



// Set the camera to an arbitrary location without changing orientation
void Camera::setPosition(const glm::vec3& pos)
{
    position_ = pos;
}



// Set the orientation of the camera without changing its position_
void Camera::lookAt(const glm::vec3& newLookVector, const glm::vec3& newUpVector_)
{
    lookDirection_ = newLookVector;
    upVector_ = newUpVector_;
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
    glm::vec4 pos(position_, 1.0);
    glm::vec4 look(lookDirection_, 1.0);
    glm::mat4 matrix = glm::translate(glm::mat4(), xyzTheta);
    pos = matrix * pos;
    look = matrix * look;

    position_ = pos.xyz();
    lookDirection_ = look.xyz();
}



// Pitch the camera along the axis orthogonal to the up and look vectors
void Camera::pitch(float theta)
{
    glm::mat4 matrix = glm::rotate(glm::mat4(), theta,
                                   glm::cross(lookDirection_, upVector_));

    glm::vec4 look(lookDirection_, 0.0);
    lookDirection_ = (matrix * look).xyz();

    glm::vec4 up(upVector_, 0.0);
    upVector_ = (matrix * up).xyz();
}



// Yaw the camera along the up vector
void Camera::yaw(float theta)
{
    glm::mat4 matrix = glm::rotate(glm::mat4(), theta, upVector_);

    glm::vec4 look(lookDirection_, 0.0);
    lookDirection_ = (matrix * look).xyz();
}



// Roll the camera along the look axis
void Camera::roll(float theta)
{
    glm::mat4 matrix = glm::rotate(glm::mat4(), theta, lookDirection_);

    glm::vec4 up(upVector_, 0.0);
    upVector_ = (matrix * up).xyz();
}



// Sets the perspective of the camera
void Camera::setPerspective(
    float fieldOfView_Degrees, float aspectRatio_,
    float nearclipdistance, float farclipdistance
)
{
    this->fieldOfView_   = fieldOfView_Degrees;
    this->aspectRatio_   = aspectRatio_;
    this->nearFieldClip_ = nearclipdistance;
    this->farFieldClip_  = farclipdistance;
    this->projection_ = glm::perspective(fieldOfView_, aspectRatio_, nearFieldClip_, farFieldClip_);
}



void Camera::setFieldOfView(float degrees)
{
    fieldOfView_ = degrees;
    projection_ = glm::perspective(fieldOfView_, aspectRatio_,
                                  nearFieldClip_, farFieldClip_);
}



void Camera::setAspectRatio(float ratio)
{
    aspectRatio_ = ratio;
    projection_ = glm::perspective(fieldOfView_, aspectRatio_,
                                  nearFieldClip_, farFieldClip_);
}



void Camera::setNearFieldClipDistance(float distance)
{
    nearFieldClip_ = distance;
    projection_ = glm::perspective(fieldOfView_, aspectRatio_,
                                  nearFieldClip_, farFieldClip_);
}



void Camera::setFarFieldClipDistance(float distance)
{
    farFieldClip_ = distance;
    projection_ = glm::perspective(fieldOfView_, aspectRatio_,
                                  nearFieldClip_, farFieldClip_);
}



//accessors:

glm::vec3 Camera::getLookDirection() const
{
    return lookDirection_;
}



glm::vec3 Camera::getPosition() const
{
    return position_;
}



glm::vec3 Camera::getUpVector() const
{
    return upVector_;
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

    ss << "LookV: <" << lookDirection_.x << ", " << lookDirection_.y <<
                    ", " << lookDirection_.z << "> ";
    ss << "UpV: <"   << upVector_.x << ", " << upVector_.y <<
                    ", " << upVector_.z << "> ";
    ss << "Pos: <"   << position_.x << ", " << position_.y <<
                    ", " << position_.z << ">";

    return ss.str();
}
