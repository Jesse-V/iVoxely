
#include "Ground.hpp"
#include "Rendering/DataBuffers/VertexBuffer.hpp"
#include "Rendering/DataBuffers/NormalBuffer.hpp"
#include <iostream>


std::shared_ptr<RenderableObject> Ground::makeObject()
{
	auto program = cs5400::makeProgram(
		cs5400::makeVertexShader("Models/Ground/vertex.glsl"),
		cs5400::makeFragmentShader("Models/Ground/fragment.glsl")
	);

	return std::make_shared<RenderableObject>(program, getDataBuffers());
}



std::vector<std::shared_ptr<DataBuffer>> Ground::getDataBuffers()
{
	std::cout << "Assembling Ground Model, making... ";
	std::vector<std::shared_ptr<DataBuffer>> buffers;

	auto vertices = getVertices();
	auto triangles = getTriangles();

	auto vBuffer = std::make_shared<VertexBuffer>(vertices, triangles);
	buffers.push_back(vBuffer);

	auto normals = getNormals(vertices, triangles);
	auto nBuffer = std::make_shared<NormalBuffer>(normals);
	buffers.push_back(nBuffer);

	return buffers;
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
	return NormalBuffer::calcNormalsMWE(vertices, triangles);
}
