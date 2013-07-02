
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

    public: //structs
        enum class CubeType : unsigned int
        {
            DIRT
        };

    public: //methods
        Cube(CubeType cubeType, int x, int y, int z);
        std::string getTexturePath(CubeType CubeType);
        std::shared_ptr<cs5400::Program> getProgram();
        std::shared_ptr<TextureBuffer> getTextureBuffer();
        void initializeAndStore(std::shared_ptr<cs5400::Program> program);

        static std::shared_ptr<Mesh> getMesh();
        static std::shared_ptr<NormalBuffer> getNormalBuffer();
        static std::vector<GLfloat> getCoordinateMap();

    private: //structs
        struct CubeAttributes
        {
            std::shared_ptr<TextureBuffer> textureBuffer;
            std::shared_ptr<cs5400::Program> program;
        };

        struct CubeTypeHash
        {
            std::size_t operator()(const CubeType& myEnum) const
            {
                return static_cast<std::size_t>(myEnum);
            }
        };

    private: //methods
        std::vector<std::shared_ptr<OptionalDataBuffer>> assembleDataBuffers(CubeType CubeType);

    private: //data
        CubeType cubeType; //identifies the cube

        static std::shared_ptr<Mesh> mesh_;
        static std::shared_ptr<NormalBuffer> normalBuffer_;
        static std::unordered_map<CubeType, CubeAttributes, CubeTypeHash> cache_;
};

#endif
