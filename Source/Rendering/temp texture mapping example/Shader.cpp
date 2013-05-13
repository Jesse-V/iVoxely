#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include "Shader.h"


namespace 
{
  std::string getCode(std::string path)
  {
    std::string contents;
    std::ifstream fin(path,std::ios::in | std::ios::binary);
    if(!fin.good())
    {
      throw std::runtime_error("Could not open shader file: " + path);
    }
    fin.seekg(0,std::ios::end);
    contents.resize(fin.tellg());
    fin.seekg(0,std::ios::beg);
    fin.read(&contents[0],contents.size());
    fin.close();
  #ifdef GL_ES_VERSION_2_0
    std::string header = "#version 100\n"
			"#define GLES2\n";
  #else
    std::string header = "#version 330\n";
  #endif   
    return header + contents;
  }
  void print_log(GLuint object)
  {
	  GLint log_length = 0;
  if (glIsShader(object))
    glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
  else if (glIsProgram(object))
    glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
  else {
    fprintf(stderr, "printlog: Not a shader or a program\n");
    return;
  }
 
  char* log = (char*)malloc(log_length);
 
  if (glIsShader(object))
    glGetShaderInfoLog(object, log_length, NULL, log);
  else if (glIsProgram(object))
    glGetProgramInfoLog(object, log_length, NULL, log);
 
  fprintf(stderr, "%s", log);
  free(log);
  }
  
  void setCode(GLuint handle,const std::string & code)
  {
    const GLchar* source[1] = {code.c_str()};
    glShaderSource(handle,1,source,NULL);
    glCompileShader(handle);
    GLint compile_ok = GL_FALSE;
    glGetShaderiv(handle,GL_COMPILE_STATUS,&compile_ok);
    if(compile_ok == GL_FALSE)
	{
	  print_log(handle);
      throw std::runtime_error("Shader failed to compile");
	}

  }

  
}


template<typename T>
std::shared_ptr<cs5400::Shader<T>> make_shader(std::string path)
{
  auto code = getCode(path);
  auto shader = std::make_shared<cs5400::Shader<T>>();
  setCode(shader->getHandle(),code);
  return shader;
}

std::shared_ptr<cs5400::VertexShader> cs5400::make_vertexShader(std::string path)
{
  return make_shader<detail::VertexShaderTag>(path);
}

std::shared_ptr<cs5400::FragmentShader> cs5400::make_fragmentShader(std::string path)
{
  return make_shader<detail::FragmentShaderTag>(path);
}
