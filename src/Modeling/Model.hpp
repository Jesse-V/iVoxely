
#ifndef MODEL
#define MODEL

#include "Modeling/Mesh/Mesh.hpp"
#include "Modeling/DataBuffers/OptionalDataBuffer.hpp"
#include "Modeling/Shading/Program.hpp"
#include "glm/glm.hpp"
#include <vector>
#include <memory>

typedef std::vector<std::shared_ptr<OptionalDataBuffer>> BufferList;

class Model
{
    public:
        Model(const std::shared_ptr<Mesh>& mesh);
        Model(const std::shared_ptr<Mesh>& mesh, const BufferList& optionalDBs);
        Model(const std::shared_ptr<Mesh>& mesh, const BufferList& optionalDBs,
                GLenum renderMode);

        virtual void initializeAndStore(const ProgramPtr& program);
        void setVisible(bool visible);
        void setModelMatrix(const glm::mat4& matrix); // model -> world coords
        void setRenderMode(GLenum newMode);
        void render(GLint modelMatrixID);

        virtual ProgramPtr getProgram();
        BufferList getOptionalDataBuffers();
        bool hasBeenInitialized();

    private:
        void enableDataBuffers();
        void disableDataBuffers();

    protected:
        std::shared_ptr<Mesh> mesh_;
        BufferList optionalDBs_;
        ProgramPtr renderingProgram_;
        glm::mat4 modelMatrix_;
        bool isVisible_, beenInitialized_;
        GLenum renderMode_;
};

#endif
