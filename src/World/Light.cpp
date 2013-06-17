
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
