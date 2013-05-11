#ifndef CS5400_PROGRAM
#define CS5400_PROGRAM

#include <memory>

#include "Shader.h"

namespace cs5400
{
  class Program
  {
  public:
    Program(
      std::shared_ptr<VertexShader> vertex_
     ,std::shared_ptr<FragmentShader> fragment_)
    :handle(glCreateProgram())
    ,vertex(vertex_)
    ,fragment(fragment_)
    {}
    GLuint getHandle(){return handle;}
    ~Program()
    {
      //glDeleteProgram(handle);
    }
  private:
    GLuint handle;
    std::shared_ptr<VertexShader> vertex;
    std::shared_ptr<FragmentShader> fragment;
  };
  
  std::shared_ptr<Program> make_program(std::shared_ptr<VertexShader> vertex,std::shared_ptr<FragmentShader> fragment);
}

#endif