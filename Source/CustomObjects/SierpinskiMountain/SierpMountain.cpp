
#include "SierpMountain.hpp"
#include "Modeling/DataBuffers/VertexBuffer.hpp"
#include <algorithm>
#include <map>
#include <iostream>


std::shared_ptr<RenderableObject> SierpMountain::makeObject()
{
	auto program = cs5400::makeProgram(
		cs5400::makeVertexShader("CustomObjects/SierpinskiMountain/vertex.glsl"),
		cs5400::makeFragmentShader("CustomObjects/SierpinskiMountain/fragment.glsl")
	);

	return std::make_shared<RenderableObject>(program, getDataBuffers());
}



std::vector<std::shared_ptr<DataBuffer>> SierpMountain::getDataBuffers()
{
	std::vector<std::shared_ptr<DataBuffer>> buffers;

	auto vBuffer = std::make_shared<VertexBuffer>(getMesh());
	buffers.push_back(vBuffer);

	return buffers;
}



std::shared_ptr<Mesh> SierpMountain::getMesh()
{
	auto mesh = std::make_shared<Mesh>();

	std::cout << "Assembling Sierpinski Mountain, making... ";

	std::cout << "vertices... ";
	addVertices(mesh);

	std::cout << "triangles... ";
	addIndices(mesh);

	std::cout << "normals... ";
	mesh->calcNormalsMWE();

	std::cout << "done" << std::endl;
	std::cout << "vertex count: " << mesh->vertices.size() << std::endl;

	return mesh;
}



void SierpMountain::addVertices(std::shared_ptr<Mesh>& mesh)
{
	std::vector<TriangleFace> modelTriangles;
	createMountain(modelTriangles);

	for_each (modelTriangles.begin(), modelTriangles.end(), //iterate through all the gasket's triangles
		[&](const TriangleFace& triangle)
		{
			mesh->vertices.push_back(glm::vec3(triangle.A.x, triangle.A.z, triangle.A.y));
			mesh->vertices.push_back(glm::vec3(triangle.B.x, triangle.B.z, triangle.B.y));
			mesh->vertices.push_back(glm::vec3(triangle.C.x, triangle.C.z, triangle.C.y));
		});
}



void SierpMountain::addIndices(std::shared_ptr<Mesh>& mesh)
{
	for (unsigned int j = 0; j < mesh->vertices.size() - 2; j += 3)
		mesh->triangles.push_back(Triangle(j + 2, j + 1, j));
}



/* Creates all four faces of the 3D mountain and returns the result */
void SierpMountain::createMountain(std::vector<TriangleFace>& modelTriangles)
{
	auto oppositeCorners = std::make_pair(BASE[0], BASE[2]);

	auto topPeak = getMidpoint(oppositeCorners.first, oppositeCorners.second);
	topPeak.z = 1;

	createFace(modelTriangles, {topPeak, BASE[0], BASE[1]}, RESOLUTION);
	createFace(modelTriangles, {topPeak, BASE[1], BASE[2]}, RESOLUTION);
	createFace(modelTriangles, {topPeak, BASE[2], BASE[3]}, RESOLUTION);
	createFace(modelTriangles, {topPeak, BASE[3], BASE[0]}, RESOLUTION);
}



/* Creates a face of the mountain by divide and conquer */
void SierpMountain::createFace(std::vector<TriangleFace>& modelTriangles, const TriangleFace& baseTriangle, int depthLeft)
{
	if (depthLeft <= 0) //base case
	{
		modelTriangles.push_back(baseTriangle);
		return;
	}

	//subdivide and recurse
	auto subTriangles = subdivideTriangle(baseTriangle);
	for_each (subTriangles.begin(), subTriangles.end(),
		[&](const TriangleFace& subTri)
		{
			createFace(modelTriangles, subTri, depthLeft - 1);
		});
}



/* Subdivides the triangle into four separate equilateral triangles and returns the result */
std::vector<TriangleFace> SierpMountain::subdivideTriangle(const TriangleFace& triangle)
{
	/*
				  A
				  /\
				 /  \
			  c'/____\b'
			   /\    /\
			  /  \  /  \
			 /____\/____\
			B     a'     C
	*/

	auto aPrime = getMidpoint(triangle.B, triangle.C);
	auto bPrime = getMidpoint(triangle.C, triangle.A);
	auto cPrime = getMidpoint(triangle.A, triangle.B);

	return {
		{ triangle.A, cPrime, bPrime }, //top triangle
		{ cPrime, triangle.B, aPrime }, //bottom left triangle
		{ bPrime, aPrime, triangle.C }, //bottom right triangle
		{ cPrime, aPrime, bPrime }      //center triangle
	};
}




/*	Returns the midpoint between the two points with a randomized offset.
	Uses memoizing to avoid tearing across repeated lookups. */
Point SierpMountain::getMidpoint(const Point& a, const Point& b)
{
	static std::map<std::pair<Point, Point>, Point> memo;
	auto AB = std::make_pair(a, b), BA = std::make_pair(b, a);

	auto foundResult = memo.find(AB);
	if (foundResult != memo.end())
		return foundResult->second; //if found in cache, return pre-computed midpoint

	auto result = (a + b) / 2; //create midpoint
	result += randVector() * Point::length(a, b) * RANDOMNESS_SCALE; //add random offset

	memo.insert(std::make_pair(AB, result)); //memoize
	memo.insert(std::make_pair(BA, result));

	return result;
}



/* Produces a vector with the coordinates randomized and in the range of (-1, 1) */
Point SierpMountain::randVector()
{
	static std::mt19937 mersenneTwister; //Mersenne Twister PRNG. WAY better randomness!
	static std::uniform_real_distribution<float> randomFloat(-1, 1);

	return {
		randomFloat(mersenneTwister),
		randomFloat(mersenneTwister),
		randomFloat(mersenneTwister)
	};
}
