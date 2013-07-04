
#include "TextureBuffer.hpp"


TextureBuffer::TextureBuffer(
    const std::string& imagePath,
    const std::vector<GLfloat>& coordinateMap):
    SampledBuffer(imagePath, coordinateMap)
{}



void TextureBuffer::initialize(GLuint programHandle)
{
    SampledBuffer::initialize(programHandle);
    attribute_texcoord_ = glGetAttribLocation(programHandle, "texcoord");
}



void TextureBuffer::store()
{
    SampledBuffer::store();
    glVertexAttribPointer(attribute_texcoord_, 2, GL_FLOAT, GL_FALSE, 0, 0);
}



void TextureBuffer::enable()
{
    glEnableVertexAttribArray(attribute_texcoord_);
}



void TextureBuffer::disable()
{
    glDisableVertexAttribArray(attribute_texcoord_);
}



SnippetPtr TextureBuffer::getVertexShaderGLSL()
{
    return std::make_shared<ShaderSnippet>(
        R".(
            //TextureBuffer fields
            attribute vec2 texcoord;
            out vec2 UV;
        ).",
        R".(
            //TextureBuffer methods
        ).",
        R".(
            //TextureBuffer main method code
            UV = texcoord;
        )."
    );
}



SnippetPtr TextureBuffer::getFragmentShaderGLSL()
{
    return std::make_shared<ShaderSnippet>(
        R".(
            //TextureBuffer fields
            uniform sampler2D textureSampler;
            in vec2 UV;
        ).",
        R".(
            //TextureBuffer methods
        ).",
        R".(
            //TextureBuffer main method code
            vec3 textureColor = texture(textureSampler, UV).rgb;
        )."
    );
}
