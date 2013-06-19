
#include "ShaderManager.hpp"
#include <sstream>
#include <algorithm>
#include <iostream>


GLuint ShaderManager::createProgram(
	const std::shared_ptr<RenderableObject>& obj,
	const std::shared_ptr<ShaderSnippet>& sceneVertexShader,
	const std::shared_ptr<ShaderSnippet>& sceneFragmentShader,
	const std::vector<std::shared_ptr<Light>> lights
)
{
	auto dataBuffers = obj->getAllDataBuffers();
	auto vertexSnippets = assembleVertexSnippets(sceneVertexShader, dataBuffers, lights);
	auto fragmentSnippets = assembleFragmentSnippets(sceneFragmentShader, dataBuffers, lights);

	sceneVertexShader
	auto lightVertexSnippet = lights[0]->getVertexShaderGLSL();




	std::stringstream stream("");
	stream << sceneVertexShader->getFields() << lightVertexSnippet->getFields();

	auto dataBuffers = obj->getAllDataBuffers();
	for_each (dataBuffers.begin(), dataBuffers.end(),
		[&](const std::shared_ptr<DataBuffer>& buffer)
		{
			stream << buffer->getVertexShaderGLSL()->getFields();
		}
	);

	std::cout << stream.str() << std::endl;


	//std::string vertexShaderFields = stream.str();

	return 5;
}



std::vector<ShaderSnippet> ShaderManager::assembleVertexSnippets(
	const std::shared_ptr<ShaderSnippet>& sceneVertexShader,
	const std::vector<std::shared_ptr<Light>> lights,
	const std::vector<std::shared_ptr<DataBuffer>>& dataBuffers
)
{
	std::vector<ShaderSnippet> vertexSnippets();
	vertexSnippets.push_back(sceneVertexShader);

	std::vector<ShaderSnippet> dataBufferVertexSnippets;
	//dataBufferVertexSnippets.ensureCapacity(dataBuffers.size());

	for_each (dataBuffers.begin(), dataBuffers.end(),
		[&](const std::shared_ptr<DataBuffer>& buffer)
		{
			dataBufferVertexSnippets.push_back(buffer->getVertexShaderGLSL());
		}
	);


	for_each (lights.begin(), lights.end(),
		[&](const std::shared_ptr<DataBuffer>& buffer)
		{

		}
	);
}



std::vector<ShaderSnippet> ShaderManager::assembleFragmentSnippets(
	const std::shared_ptr<RenderableObject>& obj,
	const std::shared_ptr<ShaderSnippet>& sceneFragmentShader,
	const std::vector<std::shared_ptr<Light>> lights
)
{

}




/* //Common shader:

#SAFE_FIELDS#
#OPTIONAL_FIELDS#

#SAFE_METHODS#
#OPTIONAL_METHODS#

void main()
{
	#SAFE_BODY#
	#OPTIONAL_BODY#
}

*/
