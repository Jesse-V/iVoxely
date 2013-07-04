
#include "Light.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <stdexcept>


Light::Light(const glm::vec3& position, const glm::vec3& color, float power):
    position_(position), color_(color), power_(power), emitting_(true)
{}



glm::vec3 Light::getPosition() const
{
    return position_;
}



void Light::setPosition(const glm::vec3& newPos)
{
    position_ = newPos;
}



glm::vec3 Light::getColor() const
{
    return color_;
}



void Light::setColor(const glm::vec3& newColor)
{
    color_ = newColor;
}



float Light::getPower() const
{
    return power_;
}



void Light::setPower(float power_)
{
    this->power_ = power_;
}



bool Light::isEmitting() const
{
    return emitting_;
}



// Turn the light on or off
void Light::setEmitting(bool emitting)
{
    emitting_ = emitting;
}



void Light::sync(GLuint handle)
{
    GLint lightPosUniform = glGetUniformLocation(handle, "lightPos");
    glUniform3fv(lightPosUniform, 1, glm::value_ptr(getPosition()));

   /* GLint lightColorUniform = glGetUniformLocation(handle, "lights[0].color");
    glUniform3fv(lightColorUniform, 1, glm::value_ptr(getColor()));

    GLint lightPowUniform = glGetUniformLocation(handle, "lights[0].power");
    float power_ = isEmitting() ? getPower() : 0;
    glUniform1f(lightPowUniform, power_);*/

    if (lightPosUniform < 0/* || lightColorUniform < 0 || lightPowUniform < 0*/)
        throw std::runtime_error("Unable to find Light uniform variables!");
}



std::shared_ptr<ShaderSnippet> Light::getVertexShaderGLSL()
{
    return std::make_shared<ShaderSnippet>(
        R".(
            //Light fields
            uniform vec3 lightPos;
            out vec4 fragmentPosition;
        ).",
        R".(
            //Light methods
        ).",
        R".(
            //Light main method code
            fragmentPosition = projMatrix * modelMatrix * vec4(vertex, 1);
        )."
    );
}



std::shared_ptr<ShaderSnippet> Light::getFragmentShaderGLSL()
{
    //http://www.opengl.org/discussion_boards/showthread.php/164100-GLSL-multiple-lights
    //http://en.wikibooks.org/wiki/GLSL_Programming/GLUT/Multiple_Lights
    //http://www.geeks3d.com/20091013/shader-library-phong-shader-with-multiple-lights-glsl/
    //http://gamedev.stackexchange.com/questions/53822/variable-number-of-lights-in-a-glsl-shader
    //http://stackoverflow.com/questions/8202173/setting-the-values-of-a-struct-array-from-js-to-glsl

    return std::make_shared<ShaderSnippet>(
        R".(
            //Light fields
            // http://stackoverflow.com/questions/8202173/setting-the-values-of-a-struct-array-from-js-to-glsl

            uniform vec3 lightPos;
            in vec4 fragmentPosition;
        ).",
        R".(
            //Light methods
        ).",
        R".(
            //Light main method code

            float xDist = abs(fragmentPosition.x - lightPos.x);
            float yDist = abs(fragmentPosition.y - lightPos.y);
            float zDist = abs(fragmentPosition.z - lightPos.z);

            float distance = sqrt(xDist * xDist + yDist * yDist + zDist * zDist);

            float scaledDistance = distance * 0.8;
            gl_FragColor = vec4(1) * (1 - scaledDistance);
        )."
    );
}
