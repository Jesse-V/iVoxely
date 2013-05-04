
#ifndef RENDERABLE_OBJECT_HPP
#define RENDERABLE_OBJECT_HPP

#include <memory>
#include <vector>
#include "glm/glm.hpp"
#include "DataBuffers/DataBuffer.hpp"
#include "ShaderLoader/Program.hpp"

class RenderableObject
{
	public:
		RenderableObject(const std::shared_ptr<cs5400::Program>& program, const std::vector<std::shared_ptr<DataBuffer>>& dataBuffers);
		void setVisible(bool visible);
		void setModelMatrix(const glm::mat4& matrix); // model coords -> world coords matrix
		void render(GLint modelMatrixID);

		std::shared_ptr<cs5400::Program> getProgram();

	private:
		void enableDataBuffers();
		void disableDataBuffers();

	private:
		std::shared_ptr<cs5400::Program> program;
		std::vector<std::shared_ptr<DataBuffer>> dataBuffers;
		glm::mat4 modelMatrix;
		bool isVisible;
};

#endif
