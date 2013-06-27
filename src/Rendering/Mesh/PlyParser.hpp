
#ifndef PLY_PARSER_HPP
#define PLY_PARSER_HPP

#include "Mesh.hpp"
#include "Rendering/Triangle.struct"
#include "glm/gtc/type_ptr.hpp"
#include <GL/glut.h>
#include <vector>
#include <memory>
#include <string>

class PlyParser
{
    public:
        static std::shared_ptr<Mesh> getMesh(const std::string& fileName);

    private:
        static std::string readFile(const std::string& fileContents);
        static std::vector<std::string> seperatePly(const std::string& fileContents);
        static std::vector<glm::vec3> parseVertices(const std::string& verticesData);
        static std::vector<Triangle> parseTriangles(const std::string& triangleData);
        static std::pair<int, int> getSizes(const std::string& header);
        static int getLastWordAsInt(const std::string& str);
};

#endif
