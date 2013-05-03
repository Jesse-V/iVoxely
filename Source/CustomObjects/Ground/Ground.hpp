
#ifndef GROUND_HPP
#define GROUND_HPP

#include "CustomObjects/CustomObject.hpp"

class Ground: public CustomObject
{
	public:
		virtual std::shared_ptr<RenderableObject> makeObject();

	protected:
		virtual std::vector<std::shared_ptr<DataBuffer>> getDataBuffers();
		virtual std::shared_ptr<Mesh> getMesh();
		virtual void addVertices(std::shared_ptr<Mesh>& mesh);
		virtual void addIndices(std::shared_ptr<Mesh>& mesh);
};

#endif
