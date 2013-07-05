
#include "Scene.hpp"
#include "Modeling/Shading/ShaderManager.hpp"
#include "Modeling/DataBuffers/NormalBuffer.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <algorithm>
#include <sstream>
#include <iostream>


Scene::Scene(const std::shared_ptr<Camera>& camera):
    camera_(camera)
{}



void Scene::addModel(const std::shared_ptr<Model>& model)
{
    models_.push_back(model);
   // std::cout << "Successfully added a Model to the Scene" << std::endl;
}



void Scene::addLight(const std::shared_ptr<Light>& light)
{
    assertModelsContainNormalBuffers();
    lights_.push_back(light);
    std::cout << "Successfully added a Light to the Scene" << std::endl;
}



void Scene::setCamera(const std::shared_ptr<Camera>& sceneCamera)
{
    camera_ = sceneCamera;
}



void Scene::setAmbientLight(const glm::vec3& rgb)
{
    ambientLight_ = rgb;
}



//render all models and lights in the scene, as viewed from the camera_
void Scene::render()
{
    for_each (models_.begin(), models_.end(),
        [&](std::shared_ptr<Model>& model)
        {
            if (!model->isStoredOnGPU())
            {
                auto program = model->getProgram();
                if (!program)
                    program = ShaderManager::createProgram(model,
                            getVertexShaderGLSL(), getFragmentShaderGLSL(), lights_);
                model->saveAs(program);
            }

            GLuint handle = model->getProgram()->getHandle();
            glUseProgram(handle);

            camera_->sync(handle);
            syncLights(handle);

            model->render(glGetUniformLocation(handle, "modelMatrix"));
        }
    );
}



std::shared_ptr<Camera> Scene::getCamera()
{
    return camera_;
}



std::vector<std::shared_ptr<Model>> Scene::getModels()
{
    return models_;
}



LightList Scene::getLights()
{
    return lights_;
}



glm::vec3 Scene::getAmbientLight()
{
    return ambientLight_;
}



void Scene::syncLights(GLuint handle)
{
    GLint ambientLightUniform = glGetUniformLocation(handle, "ambientLight");
    glUniform3fv(ambientLightUniform, 1, glm::value_ptr(ambientLight_));

    for (std::size_t j = 0; j < lights_.size(); j++)
        lights_[j]->sync(handle, j);
}



SnippetPtr Scene::getVertexShaderGLSL()
{
    return std::make_shared<ShaderSnippet>(
        R".(
            // ********* VERTEX SHADER ********* \\

            //Scene fields
            attribute vec3 vertex; //position of the vertex
            uniform mat4 viewMatrix, projMatrix; //Camera view and projection matrices
            uniform mat4 modelMatrix; //matrix transforming model mesh into world space

            varying vec3 pos_world;
            varying vec3 eyedirection_camera;
        ).",
        R".(
            //Scene methods
            vec4 projectVertex()
            {
                mat4 MVP = projMatrix * viewMatrix * modelMatrix; //Calculate the Model-View-Projection matrix
                return MVP * vec4(vertex, 1); // Convert from model space to clip space
            }
        ).",
        R".(
            //Scene main method code
            gl_Position = projectVertex();
            pos_world = (modelMatrix * vec4(vertex, 1)).xyz; //Convert from model space to world space

            vec3 vpos_camera = (viewMatrix * modelMatrix * vec4(vertex, 1)).xyz;
            eyedirection_camera = -vpos_camera;
        )."
    );
}



SnippetPtr Scene::getFragmentShaderGLSL()
{
    return std::make_shared<ShaderSnippet>(
        R".(
            // ********* FRAGMENT SHADER ********* \\

            //Scene fields
            uniform vec3 ambientLight;
            varying vec3 pos_world;
            uniform mat4 viewMatrix, projMatrix; //Camera view and projection matrices
            uniform mat4 modelMatrix; //matrix transforming model mesh into world space

            struct ColorInfluences
            {
                vec3 textureColor, lightBlend;
            };
        ).",
        R".(
            //Scene methods
        ).",
        R".(
            //Scene main method code
            ColorInfluences colorInfluences;
            colorInfluences.textureColor = vec3(-1); //init to invalid if not needed
            colorInfluences.lightBlend = vec3(-1);
        )."
    );
}


void Scene::assertModelsContainNormalBuffers()
{
    std::vector<glm::vec3> emptyVec;
    auto normBuffer = std::make_shared<NormalBuffer>(emptyVec);
    for_each (models_.begin(), models_.end(),
        [&](std::shared_ptr<Model>& model)
        {
            auto optionalBuffers = model->getOptionalDataBuffers();
            bool containsNormalBuffer = false;
            for_each (optionalBuffers.begin(), optionalBuffers.end(),
                [&](std::shared_ptr<OptionalDataBuffer>& buffer)
                {
                    if (typeid(*buffer) == typeid(*normBuffer))
                        containsNormalBuffer = true;
                }
            );

            if (!containsNormalBuffer)
            {
                std::stringstream stream;
                stream << "Light added to Scene, yet ";
                stream << typeid(*model).name();
                stream << " does not contain a NormalBuffer!";

                throw std::runtime_error(stream.str());
            }
        }
    );
}
