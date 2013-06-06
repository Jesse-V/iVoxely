
#include "Ground.hpp"
#include "Rendering/DataBuffers/VertexBuffer.hpp"
#include "Rendering/DataBuffers/IndexBuffer.hpp"
#include "Rendering/DataBuffers/NormalBuffer.hpp"
#include "Rendering/DataBuffers/MappedBuffers/TextureBuffer.hpp"
#include <iostream>


std::shared_ptr<RenderableObject> Ground::makeObject()
{
	auto program = cs5400::makeProgram(
		cs5400::makeVertexShader("Models/Ground/vertex.glsl"),
		cs5400::makeFragmentShader("Models/Ground/fragment.glsl")
	);

	std::cout << "Assembling Ground Model, loading ";

	auto vertices = getVertices();
	return std::make_shared<RenderableObject>(
		program,
		std::make_shared<VertexBuffer>(vertices),
		getOptionalDataBuffers(vertices)
	);
}



std::vector<std::shared_ptr<DataBuffer>> Ground::getOptionalDataBuffers(const std::vector<glm::vec3>& vertices)
{
	std::vector<std::shared_ptr<DataBuffer>> optionalBuffers;

	auto triangles = getTriangles();
	auto iBuffer = std::make_shared<IndexBuffer>(triangles);
	optionalBuffers.push_back(iBuffer);

	auto normals = getNormals(vertices, triangles);
	auto nBuffer = std::make_shared<NormalBuffer>(normals);
	optionalBuffers.push_back(nBuffer);

	std::cout << "texture... ";
	auto tBuffer = std::make_shared<TextureBuffer>("Resources/textures/test_texture.bmp");
	optionalBuffers.push_back(tBuffer);

	std::cout << " done" << std::endl;

	return optionalBuffers;
}



std::vector<glm::vec3> Ground::getVertices()
{
	std::cout << "vertices... ";

	std::vector<glm::vec3> vertices;
	vertices.push_back(glm::vec3( 1, 0, -1));
	vertices.push_back(glm::vec3(-1, 0, -1));
	vertices.push_back(glm::vec3(-1, 0,  1));
	vertices.push_back(glm::vec3( 1, 0,  1));

	return vertices;
}



std::vector<Triangle> Ground::getTriangles()
{
	std::cout << "triangles... ";

	std::vector<Triangle> triangles;
	triangles.push_back(Triangle(0, 1, 2));
	triangles.push_back(Triangle(0, 2, 3));
	return triangles;
}



std::vector<glm::vec3> Ground::getNormals(const std::vector<glm::vec3>& vertices, const std::vector<Triangle>& triangles)
{
	std::cout << "normals... ";

	return NormalBuffer::calcNormalsMWASER(vertices, triangles);
}
