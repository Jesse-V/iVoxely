
#ifndef MODEL_HPP
#define MODEL_HPP

#include <memory>
#include <vector>
#include "glm/glm.hpp"
#include "DataBuffers/DataBuffer.hpp"
#include "DataBuffers/VertexBuffer.hpp"
#include "Resources/OpenGL/Program.hpp"

class Model
{
    public:
        Model(const std::shared_ptr<Mesh>& mesh,
            const std::vector<std::shared_ptr<OptionalDataBuffer>>& optionalDBs);
        Model(const std::shared_ptr<Mesh>& mesh,
            const std::vector<std::shared_ptr<OptionalDataBuffer>>& optionalDBs);
            GLenum renderMode);

        void initializeAndStore(std::shared_ptr<cs5400::Program> program);
        void setVisible(bool visible);
        void setModelMatrix(const glm::mat4& matrix); // model -> world coords
        void setRenderMode(GLenum newMode);
        void render(GLint modelMatrixID);

        std::shared_ptr<cs5400::Program> getProgram();
        std::vector<std::shared_ptr<DataBuffer>> getAllDataBuffers();
        bool hasBeenInitialized();

    private:
        void enableDataBuffers();
        void drawDataBuffers();
        void disableDataBuffers();

    private:
        std::shared_ptr<VertexBuffer> mesh_;
        std::vector<std::shared_ptr<OptionalDataBuffer>> optionalDBs_;
        std::shared_ptr<cs5400::Program> renderingProgram_;
        glm::mat4 modelMatrix_;
        bool isVisible_, beenInitialized_;
        GLenum renderMode_;
};

#endif
