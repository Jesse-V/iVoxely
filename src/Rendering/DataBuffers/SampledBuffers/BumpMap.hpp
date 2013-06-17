
#ifndef BUMP_MAP
#define BUMP_MAP

#include "SampledBuffer.hpp"

class BumpMap: public SampledBuffer
{
	public:
		BumpMap(const std::string& mapPath);

		virtual void initialize(GLuint program);
		virtual void enable();
		virtual void disable();

	protected:
		virtual void storeImage();
		virtual void storeCoordMap();

	private:
		GLuint textureID, vbo_cube_texcoords;
		GLint attribute_texcoord;
};

#endif
