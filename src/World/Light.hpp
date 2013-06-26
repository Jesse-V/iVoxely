
#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Resources/OpenGL/ShaderUtilizer.hpp"
#include "glm/glm.hpp"
#include <GL/glew.h>

class Light: public ShaderUtilizer
{
    public:
        Light(
            const glm::vec3& position = glm::vec3(0.0, 0.0, 0.0),
            const glm::vec3& color = glm::vec3(1, 1, 1),
            float power = 0.5f
        );

        void setPosition(const glm::vec3& newPos);
        void setColor(const glm::vec3& newColor);
        void setPower(float power);
        void setEmitting(bool emitting);

        glm::vec3 getPosition() const;
        glm::vec3 getColor() const;
        float getPower() const;
        bool isEmitting() const;

        void sync(GLuint handle);

        virtual std::shared_ptr<ShaderSnippet> getVertexShaderGLSL();
        virtual std::shared_ptr<ShaderSnippet> getFragmentShaderGLSL();

    private:
        glm::vec3 position_, color_;
        float power_;
        bool emitting_;
};

#endif
