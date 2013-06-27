
#ifndef GROUND_HPP
#define GROUND_HPP

#include "Models/CustomObject.hpp"

class Ground : public CustomObject
{
    public:
        virtual std::shared_ptr<Model> makeObject();

    protected:
        virtual std::vector<std::shared_ptr<DataBuffer>>
            getOptionalDataBuffers(const std::vector<glm::vec3>& vertices);
        virtual std::vector<glm::vec3> getVertices();
        virtual std::vector<Triangle> getTriangles();
        virtual std::vector<glm::vec3> getNormals(
            const std::vector<glm::vec3>& vertices,
            const std::vector<Triangle>& triangles
        );
};

#endif
