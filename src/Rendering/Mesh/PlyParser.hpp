
#ifndef PLY_PARSER_HPP
#define PLY_PARSER_HPP

#include "MeshGenerator.hpp"
#include "Rendering/Triangle.struct"
#include "glm/gtc/type_ptr.hpp"
#include <GL/glut.h>
#include <vector>
#include <string>

class PlyParser
{
    public:
        std::shared_ptr<Mesh> getMesh(const std::string& fileName);

    private:
        std::string readFile(const std::string& fileContents);
        std::vector<std::string> seperatePly(const std::string& fileContents);
        std::vector<glm::vec3> parseVertices(std::string verticesData);
        std::vector<Triangle> parseIndices(std::string indicesData);
        std::pair<int, int> getSizes(const std::string& header);
        int getLastWordAsInt(const std::string& str);

    private:
        const std::string HEADER_DELIMITER = "end_header"; //end of header
};

#endif
