
#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Resources/OpenGL/ShaderUtilizer.hpp"
#include "glm/glm.hpp"

class Light: public ShaderUtilizer
{
	public:
		Light(const glm::vec3& position = glm::vec3(0.0, 0.0, 0.0), const glm::vec3& color = glm::vec3(1, 1, 1), float power = 20);

		void setPosition(const glm::vec3& newPos);
		void setColor(const glm::vec3& newColor);
		void setPower(float power);
		void setEmitting(bool emitting);

		glm::vec3 getPosition() const;
		glm::vec3 getColor() const;
		float getPower() const;
		bool isEmitting() const;

		virtual std::shared_ptr<ShaderSnippet> getVertexShaderGLSL();
		virtual std::shared_ptr<ShaderSnippet> getFragmentShaderGLSL();

	private:
		glm::vec3 position, color;
		float power;
		bool emitting;
};

#endif
