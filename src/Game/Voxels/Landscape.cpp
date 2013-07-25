
#include "Landscape.hpp"
#include "Modeling/Shading/ShaderManager.hpp"
#include <algorithm>
#include <iostream>


ProgramCache Landscape::programCache_;


void Landscape::generateChunk(const std::shared_ptr<Scene>& scene)
{
    static std::mt19937 mersenneTwister; //Mersenne Twister PRNG. Epic!
    static std::uniform_real_distribution<float> randomFloat(0, 1);

    std::cout << "Currently " << scene->getModelCount() <<
        " Models in Scene. Adding Cubes... " << std::endl;

    const int RADIUS = 80; //as big as possible? 500 is a pretty good size, 0.005f
    for (int x = -RADIUS; x < RADIUS; x++)
    {
        for (int y = -RADIUS; y < RADIUS; y++)
        {
            for (int z = -RADIUS; z < RADIUS; z++)
            {
                glm::vec3 position(x, y, z);
                float magnitudeSqr = glm::dot(position, position);
                float distance = magnitudeSqr - RADIUS * RADIUS;

                if (distance < 0 && distance > -RADIUS * 2) //1 layer thick
                {
                    auto type = Cube::Type::STONE;
                    auto cube = std::make_shared<Cube>(type, x, y, z);
                    addCube(cube, scene);
                }
            }
        }
    }

    std::cout << "... done adding cubes. Scene now has " <<
        scene->getModelCount() << " Models." << std::endl;

    if (scene->getModelCount() > 9000)
        std::cout << "It's over 9000!!!" << std::endl;
    
    checkGlError();
}



void Landscape::addCube(const std::shared_ptr<Cube>& cube,
                        const std::shared_ptr<Scene>& scene
)
{
    auto value = programCache_.find(cube->getType());
    if (value == programCache_.end())
    { //not in cache
        
        auto program = ShaderManager::createProgram(cube,
            scene->getVertexShaderGLSL(), scene->getFragmentShaderGLSL(),
            scene->getLights()
        );
        scene->addModel(cube, program, true); //add and saveAs
        programCache_[cube->getType()] = program; //add program to cache

        std::cout << "Cached Program for Cube::Type " << (int)cube->getType() << 
            "." << std::endl;
    }
    else
    { //already in cache
        scene->addModel(cube, value->second, false); //add, already saved
    }
}
