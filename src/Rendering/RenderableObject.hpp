
#ifndef RENDERABLE_OBJECT_HPP
#define RENDERABLE_OBJECT_HPP

#include <memory>
#include <vector>
#include "glm/glm.hpp"
#include "DataBuffers/DataBuffer.hpp"
#include "DataBuffers/VertexBuffer.hpp"
#include "Resources/OpenGL/Program.hpp"

class RenderableObject
{
	public:
		RenderableObject(const std::shared_ptr<cs5400::Program>& program, std::shared_ptr<VertexBuffer> vertexBuffer, const std::vector<std::shared_ptr<DataBuffer>>& optionalDBs, GLenum renderMode);
		RenderableObject(const std::shared_ptr<cs5400::Program>& program, std::shared_ptr<VertexBuffer> vertexBuffer, const std::vector<std::shared_ptr<DataBuffer>>& optionalDBs);
		void setVisible(bool visible);
		void setModelMatrix(const glm::mat4& matrix); // model coords -> world coords matrix
		void setRenderMode(GLenum newMode);
		void render(GLint modelMatrixID);

		std::shared_ptr<cs5400::Program> getProgram();

	private:
		void enableDataBuffers();
		void drawDataBuffers();
		void disableDataBuffers();

	private:
		std::shared_ptr<cs5400::Program> program;
		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::vector<std::shared_ptr<DataBuffer>> dataBuffers;
		glm::mat4 modelMatrix;
		bool isVisible;
		GLenum renderMode;
};

#endif
