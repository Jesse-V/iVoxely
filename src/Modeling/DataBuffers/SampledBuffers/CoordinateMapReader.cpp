
#include "CoordinateMapReader.hpp"
#include "Modeling/Mesh/PlyParser.hpp"
#include <sstream>
#include <iostream>


std::vector<GLfloat> CoordinateMapReader::getMap(const std::string& fileName)
{
    std::cout << "Loading coordinate map from " << fileName << " ... ";
    std::string fileContents = PlyParser::readFile(fileName);

    std::vector<GLfloat> map;
    std::stringstream mapStream(fileContents);

    GLfloat temp;
    mapStream >> temp;
    while (mapStream.good())
    {
        map.push_back(temp);
        mapStream >> temp;
    }

    std::cout << "done (read " << map.size() << " floats)" << std::endl;

    GLfloat cube_texcoords[2 * 4 * 6] = {
        // front
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0,
    };

    for (int i = 1; i < 6; i++)
        memcpy (&cube_texcoords[i*4*2], &cube_texcoords[0], 2*4*sizeof(GLfloat));

    for (int j = 0; j < 2*4*6; j++)
        std::cout << cube_texcoords[j] << " ";

    return map;
}
