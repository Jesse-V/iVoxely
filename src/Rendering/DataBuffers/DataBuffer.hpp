
#ifndef DATA_BUFFER
#define DATA_BUFFER

#include "Resources/OpenGL/ShaderUtilizer.hpp"
#include "Resources/OpenGL/ShaderSnippet.hpp"
#include <GL/glew.h>
#include <GL/glut.h>

class DataBuffer : public ShaderUtilizer
{
    public:
        virtual void initialize(GLuint program) = 0;
        virtual void store() = 0;
        virtual void enable() = 0;
        virtual void disable() = 0;
        virtual bool draw(GLenum mode) = 0;
};

#endif
