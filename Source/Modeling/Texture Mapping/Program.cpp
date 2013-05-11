
#include "Program.h"

  
std::shared_ptr<cs5400::Program> cs5400::make_program
(
  std::shared_ptr<cs5400::VertexShader> vertex
 ,std::shared_ptr<cs5400::FragmentShader> fragment  
)
{
  GLint link_ok = GL_FALSE;
  auto program = std::make_shared<Program>(vertex,fragment);
  glAttachShader(program->getHandle(), vertex->getHandle());
  glAttachShader(program->getHandle(), fragment->getHandle());
  glLinkProgram(program->getHandle());
  glGetProgramiv(program->getHandle(), GL_LINK_STATUS, &link_ok);
  if (!link_ok) 
  {
    throw std::runtime_error("Could not link shader program.");
  }
  return program;
}

