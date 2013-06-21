
#include "RenderableObject.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <algorithm>
#include <iostream>


RenderableObject::RenderableObject(std::shared_ptr<VertexBuffer> vertexBuffer, const std::vector<std::shared_ptr<DataBuffer>>& optionalDBs):
	RenderableObject(vertexBuffer, optionalDBs, GL_TRIANGLES)
{}



RenderableObject::RenderableObject(std::shared_ptr<VertexBuffer> vertexBuffer, const std::vector<std::shared_ptr<DataBuffer>>& optionalDBs, GLenum renderMode):
	vertexBuffer(vertexBuffer), dataBuffers(optionalDBs), modelMatrix(glm::mat4()), isVisible(true), beenInitialized(false), renderMode(renderMode)
{} //Scene will call initializeAndStore



void RenderableObject::initializeAndStore(std::shared_ptr<cs5400::Program> program)
{
	renderingProgram = program;

	vertexBuffer->initialize(program->getHandle());
	vertexBuffer->store();

	for_each (dataBuffers.begin(), dataBuffers.end(),
		[&](const std::shared_ptr<DataBuffer>& buffer)
		{
			buffer->initialize(program->getHandle());
			buffer->store();
		});

	beenInitialized = true;
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
	if (!beenInitialized)
		throw std::runtime_error("RenderableObject has not been initialized!");

	return renderingProgram;
}



std::vector<std::shared_ptr<DataBuffer>> RenderableObject::getAllDataBuffers()
{
	std::vector<std::shared_ptr<DataBuffer>> all(dataBuffers);
	all.insert(all.begin(), vertexBuffer);
	return all;
}



bool RenderableObject::hasBeenInitialized()
{
	return beenInitialized;
}



// Render the object
void RenderableObject::render(GLint modelMatrixID)
{
	if (!beenInitialized)
		throw std::runtime_error("RenderableObject has not been initialized!");

	if (isVisible)
	{
		glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		enableDataBuffers();
		drawDataBuffers();
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
