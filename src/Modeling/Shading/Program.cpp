
#include "Program.hpp"
#include <iostream>


cs5400::Program::Program(
    const std::shared_ptr<VertexShader>& vertex_,
    const std::shared_ptr<FragmentShader>& fragment_):
    handle_(glCreateProgram()), vertex_(vertex_), fragment_(fragment_)
{}



cs5400::Program::~Program()
{
    glDeleteProgram(handle_);
}



GLuint cs5400::Program::getHandle()
{
    return handle_;
}



std::shared_ptr<cs5400::Program> cs5400::makeProgram(
    const std::shared_ptr<VertexShader>& vertex,
    const std::shared_ptr<FragmentShader>& fragment
)
{
    GLint link_ok = GL_FALSE;
    auto program = std::make_shared<Program>(vertex, fragment);

    glAttachShader(program->getHandle(), vertex->getHandle());
    glAttachShader(program->getHandle(), fragment->getHandle());
    glLinkProgram (program->getHandle());
    glGetProgramiv(program->getHandle(), GL_LINK_STATUS, &link_ok);

    if (link_ok)
        std::cout << "Successfully linked shader program" << std::endl;
    else
        throw std::runtime_error("Could not link shader program.");

    return program;
}
