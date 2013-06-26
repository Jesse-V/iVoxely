
#ifndef PLY_PARSER_HPP
#define PLY_PARSER_HPP

#include "glm/gtc/type_ptr.hpp"
#include <GL/glut.h>
#include <vector>
#include <string>

class PlyParser
{
    private:
        const std::string HEADER_DELIMITER = "end_header"; //end of header

        std::vector<glm::vec3> vertices_;
        std::vector<GLuint> indices_;

        std::string readFile(const std::string& fileContents);
        std::vector<std::string> seperatePly(const std::string& fileContents);
        std::vector<glm::vec3> parseVertices(std::string verticesData);
        std::vector<GLuint> parseIndices(std::string indicesData);
        std::pair<int, int> getSizes(const std::string& header);
        int getLastWordAsInt(const std::string& str);

    public:
        void loadPlyModel(const std::string& fileName);
        std::vector<glm::vec3> getVertices();
        std::vector<GLuint> getIndices();
};

#endif
