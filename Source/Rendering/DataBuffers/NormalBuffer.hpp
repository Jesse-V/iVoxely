
#ifndef NORMAL_BUFFER
#define NORMAL_BUFFER

#include "DataBuffer.hpp"
#include "../Triangle.struct"
#include <vector>

class NormalBuffer: public DataBuffer
{
	public:
		NormalBuffer(const std::vector<glm::vec3>& normals);
		virtual void initialize(GLuint program);
		virtual void store();
		virtual void enable();
		virtual void disable();

		static std::vector<glm::vec3> calcNormalsMWA(const std::vector<glm::vec3>& vertices, const std::vector<Triangle>& triangles);
		static std::vector<glm::vec3> calcNormalsMWASER(const std::vector<glm::vec3>& vertices, const std::vector<Triangle>& triangles);
		static std::vector<glm::vec3> calcNormalsMWE(const std::vector<glm::vec3>& vertices, const std::vector<Triangle>& triangles);

	private:
		std::vector<glm::vec3> normals; // vertex normals

		GLuint normalBuffer;
		GLint normalAttrib;
};

#endif
