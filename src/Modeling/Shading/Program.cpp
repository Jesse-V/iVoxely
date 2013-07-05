
#include "Program.hpp"
#include <sstream>
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
    auto program = std::make_shared<Program>(vertex, fragment);

    glAttachShader(program->getHandle(), vertex->getHandle());
    glAttachShader(program->getHandle(), fragment->getHandle());
    glLinkProgram (program->getHandle());

    GLint link_ok = GL_FALSE;
    glGetProgramiv(program->getHandle(), GL_LINK_STATUS, &link_ok);

    GLchar buf[8192];
    glGetProgramInfoLog(program->getHandle(), sizeof(buf), NULL, buf);

    if (link_ok)
    {
        std::cout << "Attached and linked shaders. Program Info Log: " <<
            std::endl << std::endl << buf << std::endl;
    }
    else
    {
        std::stringstream stream("");
        stream << "Could not link shader program \n" << buf;
        throw std::runtime_error(stream.str());
    }


    return program;
}
