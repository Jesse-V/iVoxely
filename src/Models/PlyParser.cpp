
#include "PlyParser.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <stdexcept>


// **************  Public functions:  **************

/*  Given the address to the PLY file,
    this function loads, parses, and assembles the vertices and indices data.
    Nothing is returned, as the vertices and indices are remembered internally.
    Use getVertices() and getIndices(), respectively, to return that data.
*/
void PlyParser::loadPlyModel(const std::string& fileName)
{
    auto fileContents = readFile(fileName); //read entire file
    auto pieces = seperatePly(fileContents); //header, vertices, indices

    /*
    //use threading to parallelize the parsing
    std::thread t1( [&]() {
        vertices = parseVertices(pieces[1]);
    });

    std::thread t2( [&]() {
        indices = parseIndices(pieces[2]);
    });

    t1.join(); //wait for both threads to complete
    t2.join();
    */

    vertices_ = parseVertices(pieces[1]);
    indices_ = parseIndices(pieces[2]);
}



/*  Returns the vertices from the PLY file.
    Call loadPlyModel before calling this function.
*/
std::vector<glm::vec3> PlyParser::getVertices()
{
    return vertices_;
}



/*  Returns the indices from the PLY file.
    Call loadPlyModel before calling this function.
*/
std::vector<GLuint> PlyParser::getIndices()
{
    return indices_;
}



// **************  Private helper functions:  **************

/*  Reads the given file and returns the contents as a String */
std::string PlyParser::readFile(const std::string& fileName)
{
    std::string fileContents;
    std::ifstream fin(fileName, std::ios::in);

    if (!fin.is_open())
        throw std::runtime_error("Error opening ply file: " + fileName);

    fin.seekg(0, std::ios::end);
    fileContents.resize((unsigned long)fin.tellg()); //allocate enough space
    fin.seekg(0, std::ios::beg);
    fin.read(&fileContents[0], (long)fileContents.size()); //read entire file
    fin.close();

    return fileContents;
}



/*  Accepts the contents of the PLY file,
    returns three strings: the header, the vertices, and the indices.
    Note that no parsing is done, this function just separates the raw data.
*/
std::vector<std::string> PlyParser::seperatePly(const std::string& fileContents)
{
    std::vector<std::string> pieces;
    unsigned long headerEnd = fileContents.find(HEADER_DELIMITER);
    unsigned long dataBegin = headerEnd + HEADER_DELIMITER.size() + 1;

    std::string header = fileContents.substr(0, headerEnd - 1);
    pieces.push_back(header); //add header
    auto sizes = getSizes(header); //fetches count of vertices and indices

    //skips from the end of the header to the end of vertices data
    unsigned long location = dataBegin;
    for (int lineCount = 0; lineCount < sizes.first; lineCount++)
        location = fileContents.find('\n', location + 1);

    //add vertex data
    pieces.push_back(fileContents.substr(dataBegin, location - dataBegin));
    pieces.push_back(fileContents.substr(location + 1)); //add index data

    return pieces;
}



/*  Accepts the raw characters that represent the vertices,
    parses the characters into a list of Points and returns the result.
*/
std::vector<glm::vec3> PlyParser::parseVertices(std::string verticesData)
{
    std::vector<glm::vec3> vertices;
    std::stringstream sstream(verticesData);

    //loop through each line, pull out and store the relevant data
    std::string line;
    while (std::getline(sstream, line))
    {
        glm::vec3 pt;
        sstream >> pt.x >> pt.y >> pt.z;
        vertices.push_back(pt);
    }

    return vertices;
}



/*  Accepts the raw characters that represent the indices,
    parses the characters into a list of ints and returns the result.
*/
std::vector<GLuint> PlyParser::parseIndices(std::string indicesData)
{
    GLuint verticeCount, a, b, c;
    std::vector<GLuint> indices;
    std::stringstream sstream(indicesData);

    //loop through each line, pull out and store the relevant data
    std::string line;
    while (std::getline(sstream, line))
    {
        sstream >> verticeCount >> a >> b >> c;
        indices.push_back(a);
        indices.push_back(b);
        indices.push_back(c);
    }

    return indices;
}


/**
 * Accepts the characters that make up the header,
 * returns the count of how many vertices and
 * how many indices make up the rest of the file.
 */
std::pair<int, int> PlyParser::getSizes(const std::string& header)
{
    std::stringstream stream(header);
    std::string line;
    int vertexCount = -1, indexCount = -1;

    while (std::getline(stream, line))
    {
        if (line.find("element vertex") != std::string::npos)
            vertexCount = getLastWordAsInt(line);

        if (line.find("element face") != std::string::npos)
            indexCount = getLastWordAsInt(line);
    }

    return std::make_pair(vertexCount, indexCount);
}



/*  Given a string,
    this takes the last word (space delimited),
    converts it to an int, and returns the result.
*/
int PlyParser::getLastWordAsInt(const std::string& str)
{
    std::stringstream sstream(str.substr(str.find_last_of(' ')));

    int var;
    sstream >> var;
    return var;
}
