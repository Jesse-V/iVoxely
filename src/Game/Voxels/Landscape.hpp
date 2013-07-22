
#ifndef LANDSCAPE
#define LANDSCAPE

#include "Cube.hpp"
#include "World/Scene.hpp"
#include <unordered_map>

typedef std::unordered_map<Cube::Type, ProgramPtr, Cube::CubeTypeHash> ProgramCache;

class Landscape
{
    public:
        void generateChunk(const std::shared_ptr<Scene>& scene);
        void addCube(Cube::Type type, int x, int y, int z,
                     const std::shared_ptr<Scene>& scene
        );

    private:
        static ProgramCache programCache_;
};

#endif
