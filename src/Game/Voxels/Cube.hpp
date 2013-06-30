
#ifndef CUBE
#define CUBE

#include <unordered_map>
#include <string>

class Cube
{
    //has list of 6 neighbors. If all neighbors are there, then not visible
    //all cubes have exactly the same data, so there's no need to reassemble snippets
    //all Cubes have access to all the lights
    //Cube, like all Voxels (should that be a class?) should have a bool update()

    //I think a Cube should be a Model instead of it having a Model

    enum struct Type
    {
        DIRT
    };

    private:
        static std::unordered_map<Type, std::string> shaderCache;
};

#endif
