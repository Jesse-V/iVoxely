
#ifndef DATA_BUFFER
#define DATA_BUFFER

#include "Modeling/Shading/ShaderUtilizer.hpp"
#include "Modeling/Shading/ShaderSnippet.hpp"
#include <GL/glew.h>
#include <GL/glut.h>

class DataBuffer : public ShaderUtilizer
{
    public:
        virtual void initialize(GLuint program) = 0;
        virtual void store() = 0;
        virtual void enable() = 0;
        virtual void disable() = 0;
        virtual void draw(GLenum mode) = 0;
};

#endif
