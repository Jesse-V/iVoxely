
#ifndef CUSTOM_OBJECT
#define CUSTOM_OBJECT

#include "Rendering/RenderableObject.hpp"
#include "Rendering/Triangle.struct"
#include <memory>
#include <vector>

class CustomObject
{
    public:
        virtual std::shared_ptr<RenderableObject> makeObject() = 0;
        virtual std::vector<std::shared_ptr<DataBuffer>>
            getOptionalDataBuffers(const std::vector<glm::vec3>& vertices) = 0;

    protected:
        virtual std::vector<glm::vec3> getVertices() = 0;
        virtual std::vector<Triangle> getTriangles() = 0;
        virtual std::vector<glm::vec3> getNormals(
            const std::vector<glm::vec3>& vertices,
            const std::vector<Triangle>& triangles
        ) = 0;
};

#endif
