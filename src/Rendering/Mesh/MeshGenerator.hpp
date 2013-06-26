
#ifndef MESH_GENERATOR_HPP
#define MESH_GENERATOR_HPP

#include "Mesh.hpp"
#include <memory>

class MeshGenerator
{
    public:
        virtual std::shared_ptr<Mesh> getMesh() = 0;
};

#endif
