
#include "RenderableObject.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <algorithm>


RenderableObject::RenderableObject(const std::shared_ptr<cs5400::Program>& program, std::shared_ptr<VertexBuffer> vertexBuffer, const std::vector<std::shared_ptr<DataBuffer>>& optionalDBs):
	RenderableObject(program, vertexBuffer, optionalDBs, GL_TRIANGLES)
{}



RenderableObject::RenderableObject(const std::shared_ptr<cs5400::Program>& program, std::shared_ptr<VertexBuffer> vertexBuffer, const std::vector<std::shared_ptr<DataBuffer>>& optionalDBs, GLenum renderMode):
	program(program), vertexBuffer(vertexBuffer), dataBuffers(optionalDBs), modelMatrix(glm::mat4()), isVisible(true), renderMode(renderMode)
{
	vertexBuffer->initialize(program->getHandle());
	vertexBuffer->store();

	for_each (dataBuffers.begin(), dataBuffers.end(),
		[&](const std::shared_ptr<DataBuffer>& buffer)
		{
			buffer->initialize(program->getHandle());
			buffer->store();
		});
}



// Objects that are not 'visible' will not be rendered
void RenderableObject::setVisible(bool visible)
{
	isVisible = visible;
}



// Set the matrix to convert from model coords to world coords
void RenderableObject::setModelMatrix(const glm::mat4& matrix)
{
	modelMatrix = matrix;
}



void RenderableObject::setRenderMode(GLenum newMode)
{
	renderMode = newMode;
}



std::shared_ptr<cs5400::Program> RenderableObject::getProgram()
{
	return program;
}



// Render the object
void RenderableObject::render(GLint modelMatrixID)
{
	if (isVisible)
	{
		glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		enableDataBuffers();
		//drawDataBuffers();
		disableDataBuffers();
	}
}



void RenderableObject::enableDataBuffers()
{
	vertexBuffer->enable();

	for_each (dataBuffers.begin(), dataBuffers.end(),
		[&](const std::shared_ptr<DataBuffer>& buffer)
		{
			buffer->enable();
		});
}



void RenderableObject::drawDataBuffers()
{
	bool optionalBufferRendered = false;

	for_each (dataBuffers.begin(), dataBuffers.end(),
	[&](const std::shared_ptr<DataBuffer>& buffer)
	{
		if (buffer->draw(GL_TRIANGLES))
			optionalBufferRendered = true;
	});

	if (!optionalBufferRendered)
		vertexBuffer->draw(GL_TRIANGLES);
}



void RenderableObject::disableDataBuffers()
{
	vertexBuffer->disable();

	for_each (dataBuffers.begin(), dataBuffers.end(),
		[&](const std::shared_ptr<DataBuffer>& buffer)
		{
			buffer->disable();
		});
}
