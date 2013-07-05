
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
        enum class Type : unsigned short
        {
            DIRT
        };

        struct CubeTypeHash
        {
            std::size_t operator()(const Type& myEnum) const
            {
                return static_cast<std::size_t>(myEnum);
            }
        };

    public: //methods
        Cube(Type cubeType, int x, int y, int z);
        std::string getTexturePath(Type type);
        std::shared_ptr<TextureBuffer> getTextureBuffer();

        virtual ProgramPtr getProgram();
        virtual void saveAs(const ProgramPtr& program);

        static std::shared_ptr<Mesh> getMesh();
        static std::shared_ptr<NormalBuffer> getNormalBuffer();
        static std::vector<GLfloat> getCoordinateMap();

    private: //methods
        BufferList assembleDataBuffers(Type type);

    private: //data
        Type type_; //identifies the cube

        static std::shared_ptr<Mesh> mesh_;
        static std::shared_ptr<NormalBuffer> normalBuffer_;
        static std::unordered_map<Type, ProgramPtr, CubeTypeHash> programCache_;
};

#endif
