
#ifndef PLY_PARSER_HPP
#define PLY_PARSER_HPP

#include <vector>
#include <string>
#include "Point.hpp"

class PlyParser
{
	private:
		const std::string HEADER_DELIMITER = "end_header"; //indicates end of header

		std::vector<cs5400::Point> vertices; //PLY data
		std::vector<GLuint> indices;

		std::string readFile(const std::string& fileContents); //reads entire file
		std::vector<std::string> seperatePly(const std::string& fileContents); //seperates file
		std::vector<cs5400::Point> parseVertices(std::string verticesData); //parses out vertices
		std::vector<GLuint> parseIndices(std::string indicesData); //parses out indices
		std::pair<int, int> getSizes(const std::string& header); //fetches how many vertices/indices there are
		int getLastWordAsInt(const std::string& str); //returns last word in the string as an int

	public:
		void loadPlyModel(const std::string& fileName); //loads, parses, and assembles PLY data
		std::vector<cs5400::Point> getVertices(); //returns vertices that loadPlyModel created
		std::vector<GLuint> getIndices(); //returns indices that loadPlyModel created
};

#endif
