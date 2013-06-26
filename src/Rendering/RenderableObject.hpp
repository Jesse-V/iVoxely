
#ifndef RENDERABLE_OBJECT_HPP
#define RENDERABLE_OBJECT_HPP

#include <memory>
#include <vector>
#include "glm/glm.hpp"
#include "DataBuffers/DataBuffer.hpp"
#include "DataBuffers/VertexBuffer.hpp"
#include "Resources/OpenGL/Program.hpp"

class RenderableObject
{
    public:
        RenderableObject(std::shared_ptr<VertexBuffer> vertexBuffer,
            const std::vector<std::shared_ptr<DataBuffer>>& optionalDBs);
        RenderableObject(
            std::shared_ptr<VertexBuffer> vertexBuffer,
            const std::vector<std::shared_ptr<DataBuffer>>& optionalDBs,
            GLenum renderMode
        );

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
        std::shared_ptr<cs5400::Program> renderingProgram_;
        std::shared_ptr<VertexBuffer> vertexBuffer_;
        std::vector<std::shared_ptr<DataBuffer>> dataBuffers_;
        glm::mat4 modelMatrix_;
        bool isVisible_, beenInitialized_;
        GLenum renderMode_;
};

#endif
