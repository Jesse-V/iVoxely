
#ifndef BUMP_MAP
#define BUMP_MAP

#include "SampledBuffer.hpp"

class BumpMap: public SampledBuffer
{
    public:
        BumpMap(const std::string& mapPath);

        virtual void initialize(GLuint program);
        virtual void enable();
        virtual void disable();

        virtual std::shared_ptr<ShaderSnippet> getVertexShaderGLSL();
        virtual std::shared_ptr<ShaderSnippet> getFragmentShaderGLSL();

    protected:
        virtual void storeImage();
        virtual void storeCoordMap();

    private:

};

#endif
