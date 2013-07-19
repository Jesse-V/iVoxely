
#ifndef CAMERA
#define CAMERA

#define GLM_SWIZZLE

#include "glm/glm.hpp"
#include <GL/glew.h>
#include <memory>
#include <string>

/**
    Defines the functionality of a fisheye (perspective) camera.
    A Camera is defined by three basic vectors: its position, viewing direction,
    and what is meant by "up". Since this is a perspective camera that resembles
    natural viewing, the Camera is also defined by Field of View and Aspect Ratio
    variables. The frustum is defined by this two variables, but is bounded
    depth-wise by the near and far field clips. Only fragments of polygons within
    these clip spaces will be rendered. In the mathematics of computer graphics,
    a camera is nothing more than another matrix that is used to project a
    polygon onto the screen. It defines the "camera space".
**/
class Camera
{
    public:
        Camera();
        void reset();
        void sync(GLuint handle) const;

        // Functions to move/direct the camera
        void setPosition(const glm::vec3& pos);
        void lookAt(const glm::vec3& look,
                    const glm::vec3& up = glm::vec3(0.0, 1.0, 0.0)
        );

        void translateX(float theta);
        void translateY(float theta);
        void translateZ(float theta);
        void translate(const glm::vec3& xyzTheta);

        void roll(float theta);
        void pitch(float theta);
        void yaw(float theta);

        // Set the perspective of the camera and its clipping distances
        void setPerspective(float fieldOfViewDegrees, float aspectRatio,
                            float nearclip, float farclip);

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
        glm::vec3 lookDirection_, position_, upVector_;
        float fieldOfView_, aspectRatio_, nearFieldClip_, farFieldClip_;
        glm::mat4 projection_;
};

#endif
