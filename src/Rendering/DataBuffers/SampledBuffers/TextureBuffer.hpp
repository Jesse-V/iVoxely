
#ifndef TEXTURE_BUFFER
#define TEXTURE_BUFFER

#include "SampledBuffer.hpp"

class TextureBuffer: public SampledBuffer
{
	public:
		TextureBuffer(const std::string& imagePath);

		virtual void initialize(GLuint program);
		virtual void enable();
		virtual void disable();

		virtual std::shared_ptr<VertexShaderSnippet> getVertexShaderGLSL();
		virtual std::shared_ptr<FragmentShaderSnippet> getFragmentShaderGLSL();

	protected:
		virtual void storeImage();
		virtual void storeCoordMap();

	private:
		GLuint textureID, vbo_cube_texcoords;
		GLint attribute_texcoord;
};

#endif
