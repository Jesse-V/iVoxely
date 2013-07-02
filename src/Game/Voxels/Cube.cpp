
#include "Cube.hpp"
#include "Modeling/Mesh/PlyParser.hpp"
#include "Modeling/DataBuffers/SampledBuffers/CoordinateMapReader.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


std::shared_ptr<Mesh> Cube::mesh_;
std::shared_ptr<NormalBuffer> Cube::normalBuffer_;
std::unordered_map<Cube::Type, Cube::CubeAttributes, Cube::TypeHash> Cube::cache_;


Cube::Cube(Type cubeType, int x, int y, int z) :
    Model(Cube::getMesh(), Cube::assembleDataBuffers(cubeType))
{
    modelMatrix_ = glm::mat4();
    modelMatrix_ = glm::scale(modelMatrix_, glm::vec3(1/8.0f));
    modelMatrix_ = glm::translate(modelMatrix_, glm::vec3(x, y, z));
}



std::vector<std::shared_ptr<OptionalDataBuffer>> Cube::assembleDataBuffers(Type cubeType)
{
    std::vector<std::shared_ptr<OptionalDataBuffer>> buffers = {
        getNormalBuffer(),
        std::make_shared<TextureBuffer>(getTexturePath(cubeType), getCoordinateMap())
    };

    return buffers;
}



std::shared_ptr<Mesh> Cube::getMesh()
{
    if (!mesh_)
        mesh_ = PlyParser::getMesh("Resources/Meshes/cube.ply");
    return mesh_;
}



std::shared_ptr<NormalBuffer> Cube::getNormalBuffer()
{
    if (!mesh_)
        throw std::runtime_error("Mesh must be initialized before getting NormalBuffer");

    if (!normalBuffer_)
        normalBuffer_ = std::make_shared<NormalBuffer>(NormalBuffer::calcNormalsMWE(mesh_));
    return normalBuffer_;
}



std::vector<GLfloat> Cube::getCoordinateMap()
{
    static std::vector<GLfloat> textureCoordinateMap_;

    if (!textureCoordinateMap_.size())
        textureCoordinateMap_ = CoordinateMapReader::getMap("Resources/Coordinate Maps/cube.coord");
    return textureCoordinateMap_;
}



std::string Cube::getTexturePath(Type cubeType)
{
    //I'd like to use a switch case, but I was unable to find a way that compiles
    if (cubeType == Type::DIRT)
        return "Resources/Textures/test_texture.bmp";

    throw std::runtime_error("Unknown texture path for cube type!");
}
