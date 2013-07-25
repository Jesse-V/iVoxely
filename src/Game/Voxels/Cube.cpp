
#include "Cube.hpp"
#include "Modeling/Mesh/PlyParser.hpp"
#include "Modeling/DataBuffers/SampledBuffers/CoordinateMapReader.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>


std::shared_ptr<Mesh> Cube::mesh_;
std::shared_ptr<NormalBuffer> Cube::normalBuffer_;


Cube::Cube(Type type, int x, int y, int z) :
    Model(Cube::getMesh(), Cube::assembleDataBuffers(type))
{
    glm::vec3 vec(x, y, z);
    /*glm::vec3 up(0, 0, 1);

    float sign = z < 0 ? -1 : 1;

    //glm::lookAt really should be used for this I think
    
    modelMatrix_ = glm::rotate(glm::mat4(), sign * -5.0f, glm::cross(vec, up));*/
    modelMatrix_ = glm::scale(modelMatrix_, glm::vec3(1 / 8.0f));
    modelMatrix_ = glm::translate(modelMatrix_, vec);
}



BufferList Cube::assembleDataBuffers(Type type)
{
    type_ = type;
    BufferList buffers = { /*getNormalBuffer(),*/ getTextureBuffer() };
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
    static std::vector<GLfloat> texCoordMap_;
    static const auto SOURCE = "Resources/Coordinate Maps/cube.coord";

    if (!texCoordMap_.size())
        texCoordMap_ = CoordinateMapReader::getMap(SOURCE);
    return texCoordMap_; //return the cached value
}



std::string Cube::getTexturePath(Type type)
{
    //I'd like to use a switch case, but I was unable to find a way that compiles
    if (type == Type::DIRT)
        return "Resources/Textures/dirt.png";
    if (type == Type::STONE)
        return "Resources/Textures/stone.png";
    if (type == Type::TEST)
        return "Resources/Textures/test_texture.bmp";

    throw std::runtime_error("Unknown texture path for cube type!");
}



std::shared_ptr<TextureBuffer> Cube::getTextureBuffer()
{
    static std::unordered_map<Type, std::shared_ptr<TextureBuffer>, TypeHash> textureCache;

    auto value = textureCache.find(type_);
    if (value != textureCache.end())
        return value->second; //if cached, return it

    //if not cached, make it, and then cache it
    auto textureBuffer = std::make_shared<TextureBuffer>(
        getTexturePath(type_), getCoordinateMap()
    );
    
    textureCache[type_] = textureBuffer;

    std::cout << "Cached TextureBuffer for " << getTypeStr() << "." << std::endl;

    return textureBuffer;
}



Cube::Type Cube::getType()
{
    return type_;
}



std::string Cube::getTypeStr()
{
    if (type_ == Type::DIRT)
        return "Type::DIRT";
    if (type_ == Type::STONE)
        return "Type::STONE";
    if (type_ == Type::TEST)
        return "Type::TEST";

    throw std::runtime_error("Unknown Cube::Type enum");
}
