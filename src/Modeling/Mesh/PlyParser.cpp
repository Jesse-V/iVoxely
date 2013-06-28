
#include "PlyParser.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <stdexcept>


// **************  Public functions:  **************

/*  Given the address to the PLY file,
    this function loads, parses, and assembles the vertices and triangle data.
    Nothing is returned, as the vertices and triangle are remembered internally.
    Use getVertices() and getTriangles(), respectively, to return that data.
*/
std::shared_ptr<Mesh> PlyParser::getMesh(const std::string& fileName)
{
    std::vector<glm::vec3> vertices;
    std::vector<Triangle> triangles;

    std::cout << "Loading PLY model from " << fileName << ": ";
    auto pieces = seperatePly(readFile(fileName));

    std::cout << "parsing... ";

    //use threading to parallelize the parsing
    std::thread t1([&]() {
        vertices = parseVertices(pieces[1]);
    });

    std::thread t2( [&]() {
        triangles = parseTriangles(pieces[2]);
    });

    t1.join(); //wait for both threads to complete
    t2.join();

    std::cout << "done" << std::endl;

    auto vBuffer = std::make_shared<VertexBuffer>(vertices);
    auto iBuffer = std::make_shared<IndexBuffer>(triangles);
    return std::make_shared<Mesh>(vBuffer, iBuffer);
}



// **************  Private helper functions:  **************

/*  Reads the given file and returns the contents as a String */
std::string PlyParser::readFile(const std::string& fileName)
{
    std::string fileContents;
    std::ifstream fin(fileName, std::ios::in);

    if (!fin.is_open())
        throw std::runtime_error("Unable to open file at " + fileName);

    fin.seekg(0, std::ios::end);
    fileContents.resize((unsigned long)fin.tellg()); //allocate enough space
    fin.seekg(0, std::ios::beg);
    fin.read(&fileContents[0], (long)fileContents.size()); //read entire file
    fin.close();

    return fileContents;
}



/*  Accepts the contents of the PLY file,
    returns three strings: the header, the vertices, and the triangle.
    Note that no parsing is done, this function just separates the raw data.
*/
std::vector<std::string> PlyParser::seperatePly(const std::string& fileContents)
{
    std::string headerDelimiter = "end_header";
    std::vector<std::string> pieces;
    unsigned long headerEnd = fileContents.find(headerDelimiter);
    unsigned long dataBegin = headerEnd + headerDelimiter.size() + 1;

    std::string header = fileContents.substr(0, headerEnd - 1);
    pieces.push_back(header); //add header
    auto sizes = getSizes(header); //fetches count of vertices and triangle

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
std::vector<glm::vec3> PlyParser::parseVertices(const std::string& verticesData)
{
    std::vector<glm::vec3> vertices;
    std::stringstream sstream(verticesData);

    //loop through each line, pull out and store the relevant data
    std::string line;
    while (std::getline(sstream, line))
    {
        std::stringstream lineStream(line);

        glm::vec3 pt;
        lineStream >> pt.x >> pt.y >> pt.z;
        vertices.push_back(pt);
    }

    return vertices;
}



/*  Accepts the raw characters that represent the triangle,
    parses the characters into a list of ints and returns the result.
*/
std::vector<Triangle> PlyParser::parseTriangles(const std::string& triangleData)
{
    int dimensionality = 3;
    std::vector<Triangle> triangles;
    std::stringstream sstream(triangleData);

    //loop through each line, pull out and store the relevant data
    std::string line;
    while (std::getline(sstream, line))
    {
        std::stringstream lineStream(line);

        lineStream >> dimensionality;
        if (dimensionality != 3)
        {
            std::cout << dimensionality << std::endl;
            throw std::runtime_error(".ply file not a 3D mesh!");
        }

        Triangle triangle;
        lineStream >> triangle.a >> triangle.b >> triangle.c;
        triangles.push_back(triangle);
    }

    return triangles;
}


/**
 * Accepts the characters that make up the header,
 * returns the count of how many vertices and
 * how many triangle make up the rest of the file.
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
