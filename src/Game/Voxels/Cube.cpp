
#include "Cube.hpp"
#include "Modeling/Mesh/PlyParser.hpp"
#include "Modeling/DataBuffers/SampledBuffers/CoordinateMapReader.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


std::shared_ptr<Mesh> Cube::mesh_;
std::shared_ptr<NormalBuffer> Cube::normalBuffer_;
std::unordered_map<Cube::CubeType, Cube::CubeAttributes, Cube::CubeTypeHash> Cube::cache_;


Cube::Cube(CubeType cubeType, int x, int y, int z) :
    Model(Cube::getMesh(), Cube::assembleDataBuffers(cubeType))
{
    modelMatrix_ = glm::mat4();
    modelMatrix_ = glm::scale(modelMatrix_, glm::vec3(1 / 8.0f));
    modelMatrix_ = glm::translate(modelMatrix_, glm::vec3(x, y, z));
}



std::vector<std::shared_ptr<OptionalDataBuffer>> Cube::assembleDataBuffers(CubeType cubeType)
{
    std::vector<std::shared_ptr<OptionalDataBuffer>> buffers = {
        getNormalBuffer(), getTextureBuffer()
    };

    return buffers;
}



std::shared_ptr<Mesh> Cube::getMesh()
{
    //all Cubes have the same Mesh, but if it's not there, then make it
    if (!mesh_)
        mesh_ = PlyParser::getMesh("Resources/Meshes/cube.ply");
    return mesh_; //return the cached value
}



std::shared_ptr<NormalBuffer> Cube::getNormalBuffer()
{
    //the Mesh is necessary for NormalBuffer's calculations
    if (!mesh_)
        throw std::runtime_error("Mesh must be initialized before getting NormalBuffer");

    //all Cubes have the same NormalBuffer, so we can cache it
    if (!normalBuffer_)
        normalBuffer_ = std::make_shared<NormalBuffer>(NormalBuffer::calcNormalsMWE(mesh_));
    return normalBuffer_;
}



std::vector<GLfloat> Cube::getCoordinateMap()
{
    static std::vector<GLfloat> textureCoordinateMap_;

    if (!textureCoordinateMap_.size())
        textureCoordinateMap_ = CoordinateMapReader::getMap("Resources/Coordinate Maps/cube.coord");
    return textureCoordinateMap_; //return the cached value
}



std::string Cube::getTexturePath(CubeType cubeType)
{
    //I'd like to use a switch case, but I was unable to find a way that compiles
    if (cubeType == CubeType::DIRT)
        return "Resources/Textures/test_texture.bmp";

    throw std::runtime_error("Unknown texture path for cube CubeType!");
}



std::shared_ptr<TextureBuffer> Cube::getTextureBuffer()
{
    auto value = cache_.find(cubeType);
    if (value != cache_.end())
        return value->second.textureBuffer; //if cached, return it

    //if not cached, make it, and then cache it
    auto textureBuffer = std::make_shared<TextureBuffer>(
        getTexturePath(cubeType), getCoordinateMap()
    );
    cache_[cubeType]->second.textureBuffer = textureBuffer;
    return textureBuffer;
}




std::shared_ptr<cs5400::Program> Cube::getProgram()
{
    auto value = cache_.find(cubeType);
    if (value != cache_.end())
        return value->second.program; //if it's cached, return it

    return nullptr; //else return nothing
}



void Cube::initializeAndStore(std::shared_ptr<cs5400::Program> program)
{
    auto value = cache_.find(cubeType); //look for it in cache

    if (value == cache_.end()) //use and store it if it isn't in the cache
    {
        Model::initializeAndStore(program);

        CubeAttributes cubeAttributes;
        cubeAttributes.textureBuffer = getTextureBuffer();
        cubeAttributes.program = program;

        cache_[cubeType] = cubeAttributes;
    }
}
