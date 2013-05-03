
#include "Mandelbrot.hpp"
#include "Modeling/DataBuffers/VertexBuffer.hpp"
#include <cmath>
#include <iostream>


std::shared_ptr<RenderableObject> Mandelbrot::makeObject()
{
	auto program = cs5400::makeProgram(
		cs5400::makeVertexShader("CustomObjects/Mandelbrot/vertex.glsl"),
		cs5400::makeFragmentShader("CustomObjects/Mandelbrot/fragment.glsl")
	);

	return std::make_shared<RenderableObject>(program, getDataBuffers());
}



std::vector<std::shared_ptr<DataBuffer>> Mandelbrot::getDataBuffers()
{
	std::vector<std::shared_ptr<DataBuffer>> buffers;

	auto vBuffer = std::make_shared<VertexBuffer>(getMesh());
	buffers.push_back(vBuffer);

	return buffers;
}



std::shared_ptr<Mesh> Mandelbrot::getMesh()
{
	auto mesh = std::make_shared<Mesh>();

	std::cout << "Assembling Mandelbrot (" << (RESOLUTION * RESOLUTION) << "), making: ";

	std::cout << "vertices... ";
	addVertices(mesh);

	std::cout << "triangles... ";
	addIndices(mesh);

	std::cout << "normals... ";
	mesh->calcNormalsMWE();

	std::cout << "done" << std::endl;
	return mesh;
}



void Mandelbrot::addVertices(std::shared_ptr<Mesh>& mesh)
{
	for (float height = 0; height <= RESOLUTION; height++)
	{
		float theta = (2.25f * 2 * PI) * (height / RESOLUTION);

		float x = (float)sin(theta) * (theta * 0.01f);
		float y = (float)cos(theta) * (theta * 0.01f);

		for (float width = 0; width <= RESOLUTION; width++)
		{
			float z = 1 * (width / RESOLUTION);
			mesh->vertices.push_back(glm::vec3(x, y, z));
		}
	}
}



void Mandelbrot::addIndices(std::shared_ptr<Mesh>& mesh)
{
	for (int x = 0; x < RESOLUTION * RESOLUTION - RESOLUTION - 1; x++)
	{
		//if (x % RESOLUTION != RESOLUTION - 1)
		{
			int y = x + 1;

			int z0 = x + RESOLUTION;
			int z1 = z0 + 1;

			mesh->triangles.push_back(Triangle(x, y, z0));
			mesh->triangles.push_back(Triangle(y, z1, z0));
		}
	}
}
