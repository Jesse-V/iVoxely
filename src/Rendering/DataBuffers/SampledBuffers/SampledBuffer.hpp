
#ifndef MAPPED_BUFFER
#define MAPPED_BUFFER

#include "../DataBuffer.hpp"
#include "glm/glm.hpp"
#include <string>

class SampledBuffer: public DataBuffer
{
	public:
		SampledBuffer(const std::string& imagePath);
		~SampledBuffer();
		//default copy constructor should be fine

		std::string loadBMP(const std::string& imagePath);
		void deleteBufferFromRAM();

		virtual void store();
		virtual bool draw(GLenum mode);

		virtual std::shared_ptr<VertexShaderSnippet> getVertexShaderGLSL();
		virtual std::shared_ptr<FragmentShaderSnippet> getFragmentShaderGLSL();

	protected:
		virtual void storeImage() = 0;
		virtual void storeCoordMap() = 0;

	protected:
		int imgWidth, imgHeight;
		unsigned char* data;
		bool isValid = false;
};

#endif
