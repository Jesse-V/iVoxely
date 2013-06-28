
#include "TextureBuffer.hpp"


TextureBuffer::TextureBuffer(const std::string& imagePath):
    SampledBuffer(imagePath)
{}



void TextureBuffer::initialize(GLuint program)
{
    SampledBuffer::initialize();
    attribute_texcoord_ = glGetAttribLocation(program, "texcoord");
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



std::shared_ptr<ShaderSnippet> TextureBuffer::getVertexShaderGLSL()
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



std::shared_ptr<ShaderSnippet> TextureBuffer::getFragmentShaderGLSL()
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
