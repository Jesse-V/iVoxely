
#ifndef LANDSCAPE
#define LANDSCAPE

#include "Cube.hpp"
#include "World/Scene.hpp"
#include <unordered_map>

typedef std::unordered_map<Cube::Type, ProgramPtr, Cube::TypeHash> ProgramCache;

class Landscape
{
    public:
        void generateChunk(const std::shared_ptr<Scene>& scene);
        void addCube(const std::shared_ptr<Cube>& cube,
                     const std::shared_ptr<Scene>& scene
        );

    private:
        static ProgramCache programCache_;
};

#endif
