
#ifndef CUSTOM_OBJECT
#define CUSTOM_OBJECT

#include "Modeling/RenderableObject.hpp"
#include "Modeling/Mesh.hpp"
#include <memory>
#include <vector>

class CustomObject
{
	public:
		virtual std::shared_ptr<RenderableObject> makeObject() = 0;
		virtual std::vector<std::shared_ptr<DataBuffer>> getDataBuffers() = 0;

	protected:
		virtual std::shared_ptr<Mesh> getMesh() = 0;
		virtual void addVertices(std::shared_ptr<Mesh>& mesh) = 0;
		virtual void addIndices(std::shared_ptr<Mesh>& mesh) = 0;
};

#endif
