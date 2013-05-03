
#ifndef SIERPINSKI_MOUNTAIN_HPP
#define SIERPINSKI_MOUNTAIN_HPP

#include "CustomObjects/CustomObject.hpp"
#include "TriangleFace.struct"
#include <vector>

class SierpMountain: public CustomObject
{
	public:
		virtual std::shared_ptr<RenderableObject> makeObject();

	protected:
		virtual std::vector<std::shared_ptr<DataBuffer>> getDataBuffers();
		virtual std::shared_ptr<Mesh> getMesh();
		virtual void addVertices(std::shared_ptr<Mesh>& mesh);
		virtual void addIndices(std::shared_ptr<Mesh>& mesh);

	private:
		Point randVector();
		float length(const Point& a, const Point& b);
		Point getMidpoint(const Point& a, const Point& b);
		std::vector<TriangleFace> subdivideTriangle(const TriangleFace& triangle);
		void createFace(std::vector<TriangleFace>& modelTriangles, const TriangleFace& baseTriangle, int depthLeft);
		void createMountain(std::vector<TriangleFace>& modelTriangles);

	private:
		const std::vector<Point> BASE = {{-1, 1, 0}, {-1, -1, 0}, {1, -1, 0}, {1, 1, 0}};
		const float RANDOMNESS_SCALE = 0.085f;//shouldn't be more than 0.2
		const int RESOLUTION = 8; //8 is a good max
};

#endif
