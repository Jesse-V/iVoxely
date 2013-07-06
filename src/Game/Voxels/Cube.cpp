
#include "Cube.hpp"
#include "Modeling/Mesh/PlyParser.hpp"
#include "Modeling/DataBuffers/SampledBuffers/CoordinateMapReader.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>


std::shared_ptr<Mesh> Cube::mesh_;
std::shared_ptr<NormalBuffer> Cube::normalBuffer_;
std::unordered_map<Cube::Type, ProgramPtr, Cube::CubeTypeHash> Cube::programCache_;


Cube::Cube(Type type, int x, int y, int z) :
    Model(Cube::getMesh(), Cube::assembleDataBuffers(type))
{
    modelMatrix_ = glm::mat4();
    modelMatrix_ = glm::scale(modelMatrix_, glm::vec3(1 / 8.0f));
    modelMatrix_ = glm::translate(modelMatrix_, glm::vec3(x, y, z));
}



BufferList Cube::assembleDataBuffers(Type type)
{
    BufferList buffers = { getNormalBuffer(), getTextureBuffer() };
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
        mesh_ = getMesh();

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



std::string Cube::getTexturePath(Type type)
{
    //I'd like to use a switch case, but I was unable to find a way that compiles
    if (type == Type::DIRT)
        return "Resources/Textures/dirt.png";

    throw std::runtime_error("Unknown texture path for cube type!");
}



std::shared_ptr<TextureBuffer> Cube::getTextureBuffer()
{
    static std::unordered_map<Type, std::shared_ptr<TextureBuffer>, CubeTypeHash> textureCache;

    auto value = textureCache.find(type_);
    if (value != textureCache.end())
        return value->second; //if cached, return it

    //if not cached, make it, and then cache it
    auto textureBuffer = std::make_shared<TextureBuffer>(
        getTexturePath(type_), getCoordinateMap()
    );
    textureCache[type_] = textureBuffer;
    return textureBuffer;
}



ProgramPtr Cube::getProgram()
{
    auto value = programCache_.find(type_);
    if (value != programCache_.end())
        return value->second; //if it's cached, return it

    return nullptr; //we can't return or create it at this point
}



void Cube::saveAs(const ProgramPtr& program)
{
    auto value = programCache_.find(type_); //look for it in cache

    //use and store it if it isn't in the cache
    if (value == programCache_.end())
    {
        Model::saveAs(program);
        programCache_[type_] = program;
    }

    isStoredOnGPU_ = true;
}
