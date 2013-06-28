
#ifndef MODEL_HPP
#define MODEL_HPP

#include "Modeling/Mesh/Mesh.hpp"
#include "Modeling/DataBuffers/OptionalDataBuffer.hpp"
#include "Modeling/Shading/Program.hpp"
#include "glm/glm.hpp"
#include <vector>
#include <memory>

class Model
{
    public:
        //Model(const std::shared_ptr<Mesh>& mesh);
        Model(const std::shared_ptr<Mesh>& mesh,
            const std::vector<std::shared_ptr<OptionalDataBuffer>>& optionalDBs);
        Model(const std::shared_ptr<Mesh>& mesh,
            const std::vector<std::shared_ptr<OptionalDataBuffer>>& optionalDBs,
            GLenum renderMode);

        void initializeAndStore(std::shared_ptr<cs5400::Program> program);
        void setVisible(bool visible);
        void setModelMatrix(const glm::mat4& matrix); // model -> world coords
        void setRenderMode(GLenum newMode);
        void render(GLint modelMatrixID);

        std::shared_ptr<cs5400::Program> getProgram();
        std::vector<std::shared_ptr<OptionalDataBuffer>> getOptionalDataBuffers();
        bool hasBeenInitialized();

    private:
        void enableDataBuffers();
        void disableDataBuffers();

    private:
        std::shared_ptr<Mesh> mesh_;
        std::vector<std::shared_ptr<OptionalDataBuffer>> optionalDBs_;
        std::shared_ptr<cs5400::Program> renderingProgram_;
        glm::mat4 modelMatrix_;
        bool isVisible_, beenInitialized_;
        GLenum renderMode_;
};

#endif
