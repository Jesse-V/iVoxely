
#ifndef MAPPED_BUFFER
#define MAPPED_BUFFER

#include "../DataBuffer.hpp"
#include "glm/glm.hpp"
#include <string>

class MappedBuffer: public DataBuffer
{
	public:
		MappedBuffer(const std::string& imagePath);
		~MappedBuffer();
		//default copy constructor should be fine

		void loadBMP(const std::string& imagePath);
		void deleteBufferFromRAM();

		virtual void store();

	protected:
		virtual void storeImage() = 0;
		virtual void storeCoordMap() = 0;

	protected:
		int imgWidth, imgHeight;
		unsigned char* data;
		bool isValid = false;
};

#endif
