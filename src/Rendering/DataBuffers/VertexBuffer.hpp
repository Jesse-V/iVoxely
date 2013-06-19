
#ifndef VERTEX_BUFFER
#define VERTEX_BUFFER

#include "DataBuffer.hpp"
#include "glm/glm.hpp"
#include <vector>

class VertexBuffer: public DataBuffer
{
	public:
		VertexBuffer(const std::vector<glm::vec3>& vertices);
		virtual void initialize(GLuint program);
		virtual void store();
		virtual void enable();
		virtual void disable();
		virtual bool draw(GLenum mode);

		virtual std::shared_ptr<VertexShaderSnippet> getVertexShaderGLSL();
		virtual std::shared_ptr<FragmentShaderSnippet> getFragmentShaderGLSL();

	private:
		void storePoints();
		void enableVertices();

	private:
		static constexpr const char* VERTEX_ATTRIB_NAME = "vertex";
		std::vector<glm::vec3> vertices;

		GLuint vertexBuffer;
		GLint vertexAttrib;
};

#endif
