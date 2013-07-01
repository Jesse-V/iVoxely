
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
    //GLint lightPosUniform = glGetUniformLocation(handle, "lightPos");
    //glUniform3fv(lightPosUniform, 1, glm::value_ptr(getPosition()));

   /* GLint lightColorUniform = glGetUniformLocation(handle, "lights[0].color");
    glUniform3fv(lightColorUniform, 1, glm::value_ptr(getColor()));

    GLint lightPowUniform = glGetUniformLocation(handle, "lights[0].power");
    float power_ = isEmitting() ? getPower() : 0;
    glUniform1f(lightPowUniform, power_);*/

    //if (lightPosUniform < 0/* || lightColorUniform < 0 || lightPowUniform < 0*/)
    //    throw std::runtime_error("Unable to find Light uniform variables!");
}



std::shared_ptr<ShaderSnippet> Light::getVertexShaderGLSL()
{
    return std::make_shared<ShaderSnippet>(
        R".(
            //Light fields
            uniform vec3 lightPos;
            out vec3 VNormal;
            out vec3 VPosition;
        ).",
        R".(
            //Light methods
        ).",
        R".(
            //Light main method code
            VNormal = normalize( NormalMatrix * vertexNormal );
            VPosition = vec3( viewMatrix * vec4( vertex, 1.0 ) );
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

            in vec3 VNormal;
            in vec3 VPosition;

        ).",
        R".(
            //Light methods
        ).",
        R".(
            //Light main method code

            vec3 color = vec3(0.81, 0.71, 0.23);

            vec3 light = vec3(lightPos);
            vec3 lightdir = light - VPosition;
            vec3 reflectVec = normalize(reflect( -lightdir, VNormal ));
            vec3 viewVec = normalize( -VPosition );
            float diff = max( dot(normalize( lightdir ), VNormal ), 0.0);
            float spec = 0.0;

            if (diff > 0.0)
                spec = max(dot(reflectVec, viewVec), 0.0);

            diff =  diff * 0.6 + spec * 0.4;
            gl_FragColor = vec4( color * ( diff + spec ), 1.0 );


            /*vec4 ambientProduct = vec4(vec3(0.2), 1) + vec4(1, 0, 1, 1);
            vec4 diffuseProduct = vec4(1) + vec4(1, 0.8, 0, 1);
            vec4 specularProduct = vec4(1) + vec4(1, 0, 1, 1);
            float shininess = 5;

            vec3 N = normalize(fN);
            vec3 E = normalize(fE);
            vec3 L = normalize(fL);
            vec3 H = normalize(L + E);

            vec4 ambient = ambientProduct;

            float kD = max(dot(L, N), 0.0);
            vec4 diffuse = kD * diffuseProduct;

            float kS = pow(max(dot(N, H), 0.0), shininess);
            vec4 specular = kS * specularProduct;

            if (dot(L, N) < 0)
                specular = vec4(vec3(0), 1);

            vec4 lighting = ambient + diffuse + specular;
            //lighting *= lights[0].color;*/


             //vec4(textureColor, 1) * lighting;
        )."
    );
}
