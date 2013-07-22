
#include "Cube.hpp"
#include "Modeling/Mesh/PlyParser.hpp"
#include "Modeling/DataBuffers/SampledBuffers/CoordinateMapReader.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>


std::shared_ptr<Mesh> Cube::mesh_;
std::shared_ptr<NormalBuffer> Cube::normalBuffer_;


Cube::Cube(Type type, int x, int y, int z) :
    Model(Cube::getMesh(), Cube::assembleDataBuffers(type))
{
    modelMatrix_ = glm::mat4();
    modelMatrix_ = glm::scale(modelMatrix_, glm::vec3(1 / 8.0f));
    modelMatrix_ = glm::translate(modelMatrix_, glm::vec3(x, y, z));
}



BufferList Cube::assembleDataBuffers(Type type)
{
    type_ = type;
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
    if (type == Type::STONE)
        return "Resources/Textures/stone.png";

    throw std::runtime_error("Unknown texture path for cube type!");
}



std::shared_ptr<TextureBuffer> Cube::getTextureBuffer()
{
    static std::unordered_map<Type, std::shared_ptr<TextureBuffer>, TypeHash> textureCache;

    auto value = textureCache.find(type_);
    if (value != textureCache.end())
    {
        std::cout << "Found TextureBuffer " << value->second << " in cache." << std::endl;
        return value->second; //if cached, return it
    }

    std::cout << "Generating TextureBuffer for Cube::Type " << (int)type_ << 
        " ..." << std::endl;

    //if not cached, make it, and then cache it
    auto textureBuffer = std::make_shared<TextureBuffer>(
        getTexturePath(type_), getCoordinateMap()
    );
    textureCache[type_] = textureBuffer;

    std::cout << "... done creating TextureBuffer" << std::endl;

    return textureBuffer;
}



Cube::Type Cube::getType()
{
    return type_;
}
