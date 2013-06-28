#ifndef SHADER_SNIPPET
#define SHADER_SNIPPET

#include <string>

class ShaderSnippet
{
    public:
        ShaderSnippet();
        ShaderSnippet(const std::string& fields,
            const std::string& methods, const std::string& mainBodyCode
        );

        std::string getFields();
        std::string getMethods();
        std::string getMainBodyCode();

    private:
        std::string fields_, methods_, mainBodyCode_;
};

#endif
