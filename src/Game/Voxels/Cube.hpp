
#ifndef CUBE
#define CUBE

#include "Modeling/Model.hpp"
#include "Modeling/DataBuffers/NormalBuffer.hpp"
#include "Modeling/DataBuffers/SampledBuffers/TextureBuffer.hpp"
#include <unordered_map>
#include <string>

class Cube : public Model
{
    //has list of 6 neighbors. If all neighbors are there, then not visible
    //all cubes have exactly the same data, so there's no need to reassemble snippets
    //all Cubes have access to all the lights
    //Cube, like all Voxels (should that be a class?) should have a bool update()

    //I think a Cube should be a Model instead of it having a Model

    public:
        enum class Type : unsigned int
        {
            DIRT
        };

        Cube(Type cubeType, int x, int y, int z);
        std::string getTexturePath(Type cubeType);

        static std::shared_ptr<Mesh> getMesh();
        static std::shared_ptr<NormalBuffer> getNormalBuffer();
        static std::vector<GLfloat> getCoordinateMap();

    private:
        struct CubeAttributes
        {
            std::shared_ptr<TextureBuffer> texture;
            std::shared_ptr<cs5400::Program> program;
        };

        struct TypeHash
        {
            std::size_t operator()(const Type& myEnum) const
            {
                return static_cast<std::size_t>(myEnum);
            }
        };

        std::vector<std::shared_ptr<OptionalDataBuffer>> assembleDataBuffers(Type cubeType);

    private:
        static std::shared_ptr<Mesh> mesh_;
        static std::shared_ptr<NormalBuffer> normalBuffer_;
        static std::unordered_map<Type, CubeAttributes, TypeHash> cache_;
};

#endif
