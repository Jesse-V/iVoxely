
#include "RenderableObject.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <algorithm>
#include <stdexcept>
#include <iostream>

#include "Resources/OpenGL/Program.hpp"


RenderableObject::RenderableObject( std::shared_ptr<VertexBuffer> vertexBuffer, const std::vector<std::shared_ptr<DataBuffer>>& optionalDBs):
	RenderableObject(vertexBuffer, optionalDBs, GL_TRIANGLES)
{}



RenderableObject::RenderableObject(std::shared_ptr<VertexBuffer> vertexBuffer, const std::vector<std::shared_ptr<DataBuffer>>& optionalDBs, GLenum renderMode):
	vertexBuffer(vertexBuffer), dataBuffers(optionalDBs), modelMatrix(glm::mat4()), isVisible(true), beenInitialized(false), renderMode(renderMode)
{
	auto program = cs5400::makeProgram(cs5400::makeVertexShader("Models/Ground/vertex.glsl"), cs5400::makeFragmentShader("Models/Ground/fragment.glsl"));
	initializeAndStore(program->getHandle());
}



void RenderableObject::initializeAndStore(GLuint handle)
{
	_handle = handle;

	vertexBuffer->initialize(handle);
	vertexBuffer->store();

	for_each (dataBuffers.begin(), dataBuffers.end(),
		[&](const std::shared_ptr<DataBuffer>& buffer)
		{
			buffer->initialize(handle);
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



GLuint RenderableObject::getHandle()
{
	return _handle;
}



std::vector<std::shared_ptr<DataBuffer>> RenderableObject::getAllDataBuffers()
{
	std::vector<std::shared_ptr<DataBuffer>> all(dataBuffers);
	all.insert(all.begin(), vertexBuffer);
	return all;
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
