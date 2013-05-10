
#include <GL/glew.h>
#include <GL/glut.h>
#include "Shader.hpp"

namespace
{
	std::string getCode(const std::string& path)
	{
		std::string contents;
		std::ifstream fin(path, std::ios::in | std::ios::binary);
		if (!fin.good())
		{
			// This is simply for convenience because in my build system
			fin.open("../"+path, std::ios::in | std::ios::binary);
			if (!fin.good())
				throw std::runtime_error("Could not open shader file: " + path);
		}

		fin.seekg(0, std::ios::end);
		contents.resize((unsigned long)fin.tellg());
		fin.seekg(0, std::ios::beg);
		fin.read(&contents[0], (long)contents.size());
		fin.close();

		#ifdef GL_ES_VERSION_2_0
			std::string header = "#version 100\n"  "#define GLES2\n";
		#else
			std::string header = "#version 120\n";
		#endif
			return header + contents;
	}



	void setCode(GLuint handle, const std::string& code)
	{
		const GLchar *source[1] = { code.c_str() };
		glShaderSource(handle, 1, source, NULL);
		glCompileShader(handle);

		GLint compile_ok = GL_FALSE;
		glGetShaderiv(handle, GL_COMPILE_STATUS, &compile_ok);
		if (compile_ok == GL_FALSE)
		{
			GLchar buf[8192];
			glGetShaderInfoLog(handle, sizeof(buf), NULL, buf);
			throw std::runtime_error(buf);
		}
	}
}


template<typename T>
std::shared_ptr<cs5400::Shader<T>> make_shader(const std::string& path)
{
	auto code = getCode(path);
	auto shader = std::make_shared<cs5400::Shader<T>>();
	setCode(shader->getHandle(), code);
	return shader;
}



std::shared_ptr<cs5400::VertexShader> cs5400::makeVertexShader(const std::string& path)
{
	return make_shader<detail::VertexShaderTag>(path);
}



std::shared_ptr<cs5400::FragmentShader> cs5400::makeFragmentShader(const std::string& path)
{
	return make_shader<detail::FragmentShaderTag>(path);
}
