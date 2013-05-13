
#include "RenderableObject.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <algorithm>


RenderableObject::RenderableObject(const std::shared_ptr<cs5400::Program>& program, const std::vector<std::shared_ptr<DataBuffer>>& dataBuffers):
	program(program), dataBuffers(dataBuffers), modelMatrix(glm::mat4()), isVisible(true)
{
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
		disableDataBuffers();
	}
}



void RenderableObject::enableDataBuffers()
{
	for_each (dataBuffers.begin(), dataBuffers.end(),
		[&](const std::shared_ptr<DataBuffer>& buffer)
		{
			buffer->enable();
		});
}



void RenderableObject::disableDataBuffers()
{
	for_each (dataBuffers.begin(), dataBuffers.end(),
		[&](const std::shared_ptr<DataBuffer>& buffer)
		{
			buffer->disable();
		});
}
