
#ifndef NORMAL_BUFFER
#define NORMAL_BUFFER

#include "DataBuffer.hpp"
#include "../Triangle.struct"
#include <vector>

class NormalBuffer: public DataBuffer
{
	public:
		NormalBuffer(std::vector<glm::vec3>, std::vector<Triangle> triangles);
		virtual void initialize(GLuint program);
		virtual void store();
		virtual void enable();
		virtual void disable();

		//static void calcNormalsMWA();
		//static void calcNormalsMWASEL();
		static std::vector<glm::vec3> calcNormalsMWE(const std::vector<glm::vec3>&, const std::vector<Triangle>& triangles);
};

#endif
