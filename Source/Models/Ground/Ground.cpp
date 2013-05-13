
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
	std::vector<std::shared_ptr<DataBuffer>> buffers;

	auto vBuffer = std::make_shared<VertexBuffer>(getMesh());
	buffers.push_back(vBuffer);

	return buffers;
}



std::shared_ptr<Mesh> Ground::getMesh()
{
	auto mesh = std::make_shared<Mesh>();

	std::cout << "Assembling Ground Model (4), making... ";

	std::cout << "vertices... ";
	addVertices(mesh);

	std::cout << "triangles... ";
	addIndices(mesh);

	std::cout << "normals... ";
	mesh->normals = NormalBuffer::calcNormalsMWE(mesh->vertices, mesh->triangles);

	std::cout << "done" << std::endl;
	return mesh;
}



void Ground::addVertices(std::shared_ptr<Mesh>& mesh)
{
	mesh->vertices.push_back(glm::vec3(	1, 0, -1));
	mesh->vertices.push_back(glm::vec3(-1, 0, -1));
	mesh->vertices.push_back(glm::vec3(-1, 0,  1));
	mesh->vertices.push_back(glm::vec3(	1, 0,  1));
}



void Ground::addIndices(std::shared_ptr<Mesh>& mesh)
{
	mesh->triangles.push_back(Triangle(0, 1, 2));
	mesh->triangles.push_back(Triangle(0, 2, 3));
}
