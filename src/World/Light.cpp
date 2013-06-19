
#include "Light.hpp"


Light::Light(const glm::vec3& position, const glm::vec3& color, float power):
	position(position), color(color), power(power), emitting(true)
{}



glm::vec3 Light::getPosition() const
{
	return position;
}


void Light::setPosition(const glm::vec3& newPos)
{
	position = newPos;
}



glm::vec3 Light::getColor() const
{
	return color;
}



void Light::setColor(const glm::vec3& newColor)
{
	color = newColor;
}



float Light::getPower() const
{
	return power;
}



void Light::setPower(float power)
{
	this->power = power;
}



bool Light::isEmitting() const
{
	return emitting;
}



// Turn the light on or off
void Light::setEmitting(bool emitting)
{
	this->emitting = emitting;
}



std::shared_ptr<VertexShaderSnippet> Light::getVertexShaderGLSL()
{
	return std::make_shared<VertexShaderSnippet>(
		R".(
			//Light fields
			uniform vec3 lightPosition; //position of the light
			varying vec3 lightdirection_camera;
		).",
		R".(
			//Light methods
		).",
		R".(
			//Light main method code
			vec3 lightpos_camera = (viewMatrix * vec4(lightPosition, 1)).xyz;
			lightdirection_camera = normalize(lightpos_camera + eyedirection_camera);
		)."
	);
}



std::shared_ptr<FragmentShaderSnippet> Light::getFragmentShaderGLSL()
{
	return std::make_shared<FragmentShaderSnippet>(
		R".(
			//Light fields
			uniform vec3 lightPosition, lightColor; //Light, optional
			uniform float lightPower; //Light, optional
		).",
		R".(
			//Light methods
			float specularLighting(inout vec3 normal, inout vec3 light) //Light, optional
			{
				vec3 eye = normalize(eyedirection_camera);
				vec3 reflect = reflect(-light, normal);
				return clamp(dot(eye, reflect), 0, 1);
			}

			float diffusedLighting(inout vec3 normal, inout vec3 light) //Light, optional
			{
				return max(0.0, clamp(dot(normal, -light), 0, 1));
			}
		).",
		R".(
			//Light main method code
			float lightDistance = length(lightPosition - pos_world);
			float theta = specularLighting(normal_camera, lightdirection_camera);
			vec3 lighting = lightColor * lightPower * theta / pow(lightDistance, 2);
			//blend Light?
		)."
	);
}
