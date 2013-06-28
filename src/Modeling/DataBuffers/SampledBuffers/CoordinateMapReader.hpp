
#ifndef COORDINATE_MAP_READER
#define COORDINATE_MAP_READER

#include <vector>
#include <string>
#include <GL/glew.h>

class CoordinateMapReader
{
    public:
       static std::vector<GLfloat> getMap(const std::string& fileName);
};

#endif
