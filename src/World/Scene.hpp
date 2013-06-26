
#ifndef SCENE_HPP
#define SCENE_HPP

#include "Camera.hpp"
#include "Light.hpp"
#include "Resources/OpenGL/Program.hpp"
#include "Rendering/RenderableObject.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

class Scene
{
    public:
        Scene(const std::shared_ptr<Camera>& camera);
        void addModel(const std::shared_ptr<RenderableObject>& obj);
        void addLight(const std::shared_ptr<Light>& light);
        void setCamera(const std::shared_ptr<Camera>& camera);
        void setAmbientLight(const glm::vec3& rgb);
        void render();

        std::shared_ptr<Camera> getCamera();
        std::vector<std::shared_ptr<RenderableObject>> getRenderableObjects();
        std::vector<std::shared_ptr<Light>> getLights();
        glm::vec3 getAmbientLight();

        virtual std::shared_ptr<ShaderSnippet> getVertexShaderGLSL();
        virtual std::shared_ptr<ShaderSnippet> getFragmentShaderGLSL();

    private:
        void syncLights(GLuint handle);
        void assertRenderableObjectsContainNormalBuffers();

    private:
        std::vector<std::shared_ptr<RenderableObject>> renderableObjects_;
        std::vector<std::shared_ptr<Light>> lights_;
        std::shared_ptr<Camera> camera_;
        glm::vec3 ambientLight_;
};


#endif
