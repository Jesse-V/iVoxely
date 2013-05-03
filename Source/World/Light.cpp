
#include "Light.hpp"


Light::Light(const glm::vec3& position, const glm::vec3& color, double power):
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



double Light::getPower() const
{
	return power;
}



void Light::setPower(double power)
{
	power = power;
}



bool Light::getEmitting() const
{
	return emitting;
}



// Turn the light on or off
void setEmitting(bool emitting)
{
	emitting = true;
}
