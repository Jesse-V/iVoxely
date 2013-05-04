
#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

#include "CustomObjects/CustomObject.hpp"

class Mandelbrot: public CustomObject
{
	public:
		virtual std::shared_ptr<RenderableObject> makeObject();

	protected:
		virtual std::vector<std::shared_ptr<DataBuffer>> getDataBuffers();
		virtual std::shared_ptr<Mesh> getMesh();
		virtual void addVertices(std::shared_ptr<Mesh>& mesh);
		virtual void addIndices(std::shared_ptr<Mesh>& mesh);

	private:
		const float PI = 3.1415926535897932384626433832795f;
		const unsigned int RESOLUTION = 1024; //1024 is good resolution
};

#endif
