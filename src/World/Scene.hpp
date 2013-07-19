
#ifndef SCENE
#define SCENE

#include "Camera.hpp"
#include "Light.hpp"
#include "Modeling/Shading/Program.hpp"
#include "Modeling/Model.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

/**
    A Scene is basically a high-level container for Models, Lights, and a Camera.
    This allows for an application to use multiple Scenes for different environments
    or locations. Another advantage is that Scene::render() will handle the
    management of rendering all Models with all the Lights, as seen by the given
    Camera.
**/
class Scene
{
    public:
        Scene(const std::shared_ptr<Camera>& camera);
        void addModel(const std::shared_ptr<Model>& obj);
        void addLight(const std::shared_ptr<Light>& light);
        void setCamera(const std::shared_ptr<Camera>& camera);
        void setAmbientLight(const glm::vec3& rgb);
        void render();

        std::shared_ptr<Camera> getCamera();
        std::vector<std::shared_ptr<Model>> getModels();
        std::vector<std::shared_ptr<Light>> getLights();
        glm::vec3 getAmbientLight();

        virtual SnippetPtr getVertexShaderGLSL();
        virtual SnippetPtr getFragmentShaderGLSL();

    private:
        void syncLights(GLuint handle);
        void assertModelsContainNormalBuffers();

    private:
        std::vector<std::shared_ptr<Model>> models_;
        LightList lights_;
        std::shared_ptr<Camera> camera_;
        glm::vec3 ambientLight_;
};


#endif
