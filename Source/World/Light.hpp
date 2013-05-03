
#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "glm/glm.hpp"

class Light
{
	public:
		Light(const glm::vec3& position = glm::vec3(0.0, 0.0, 0.0), const glm::vec3& color = glm::vec3(1, 1, 1), double power = 20);

		void setPosition(const glm::vec3& newPos);
		void setColor(const glm::vec3& newColor);
		void setPower(double power);
		void setEmitting(bool emitting);

		glm::vec3 getPosition() const;
		glm::vec3 getColor() const;
		double getPower() const;
		bool getEmitting() const;

	private:
		glm::vec3 position, color;
		double power;
		bool emitting;
};

#endif
