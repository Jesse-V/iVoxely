
#ifndef CS5400_PROGRAM
#define CS5400_PROGRAM

#include <memory>
#include "Shader.hpp"

namespace cs5400
{
	class Program
	{
		public:
			Program(const std::shared_ptr<VertexShader>& vertex_, const std::shared_ptr<FragmentShader>& fragment_);
			~Program();
			GLuint getHandle();

		private:
			GLuint handle;
			std::shared_ptr<VertexShader> vertex;
			std::shared_ptr<FragmentShader> fragment;
	};

	std::shared_ptr<Program> makeProgram(const std::shared_ptr<VertexShader>& vertex, const std::shared_ptr<FragmentShader>& fragment);
}

#endif
