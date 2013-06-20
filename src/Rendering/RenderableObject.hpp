
#ifndef RENDERABLE_OBJECT_HPP
#define RENDERABLE_OBJECT_HPP

#include <memory>
#include <vector>
#include "glm/glm.hpp"
#include "DataBuffers/DataBuffer.hpp"
#include "DataBuffers/VertexBuffer.hpp"

class RenderableObject
{
	public:
		RenderableObject(std::shared_ptr<VertexBuffer> vertexBuffer, const std::vector<std::shared_ptr<DataBuffer>>& optionalDBs, GLenum renderMode);
		RenderableObject(std::shared_ptr<VertexBuffer> vertexBuffer, const std::vector<std::shared_ptr<DataBuffer>>& optionalDBs);
		void initializeAndStore(GLuint handle);
		void setVisible(bool visible);
		void setModelMatrix(const glm::mat4& matrix); // model coords -> world coords matrix
		void setRenderMode(GLenum newMode);
		void render(GLint modelMatrixID);
		GLuint getHandle();
		std::vector<std::shared_ptr<DataBuffer>> getAllDataBuffers();

	private:
		void enableDataBuffers();
		void drawDataBuffers();
		void disableDataBuffers();

	private:
		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::vector<std::shared_ptr<DataBuffer>> dataBuffers;
		glm::mat4 modelMatrix;
		bool isVisible, beenInitialized;
		GLenum renderMode;
		GLuint _handle;
};

#endif
