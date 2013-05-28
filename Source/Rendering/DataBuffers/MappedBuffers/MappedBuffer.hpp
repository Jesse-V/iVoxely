
#ifndef MAPPED_BUFFER
#define MAPPED_BUFFER

#include "../DataBuffer.hpp"
#include "glm/glm.hpp"
#include <string>

class MappedBuffer: public DataBuffer
{
	public:
		MappedBuffer(const std::string imagePath);
		void loadBMP(const std::string imagePath);

	protected:
		int imgWidth, imgHeight;
		unsigned char* data;
};

#endif
