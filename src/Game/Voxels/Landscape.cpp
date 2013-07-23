
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

    //Chunk::generateCubes(scene, 0, 0);

    const int MIN = -32;
    const int MAX = 32;

    //player should be 8 blocks tall (vs 2 in Minecraft)
    //chunks are 64*64*64

    for (int x = MIN; x < MAX; x++)
    {
        for (int y = MIN; y < MAX; y++)
        {
            for (int z = -15; z <= 0; z++)
            {
                float val = randomFloat(mersenneTwister);

                auto type = val > 0.5 ? Cube::Type::DIRT : Cube::Type::STONE;
                //std::cout << "Adding Cube, type " << (int)type << " ..." << std::endl;
                auto cube = std::make_shared<Cube>(type, x, y, z);
                addCube(cube, scene);
            }
        }
    }

    std::cout << "... done adding cubes. Scene now has " <<
        scene->getModelCount() << " Models." << std::endl;

    if (scene->getModelCount() > 9000)
        std::cout << "It's over 9000!!!" << std::endl;

    if (scene->getModelCount() > 90000)
        std::cout << "WARNING: likely FPS issues rendering that many cubes!\n";

    checkGlError();
}



void Landscape::addCube(const std::shared_ptr<Cube>& cube,
                        const std::shared_ptr<Scene>& scene
)
{
    auto value = programCache_.find(cube->getType());
    if (value == programCache_.end())
    { //not in cache
        std::cout << "No Program found in cache. Constructing... " << std::endl;

        auto program = ShaderManager::createProgram(cube,
            scene->getVertexShaderGLSL(), scene->getFragmentShaderGLSL(),
            scene->getLights()
        );
        scene->addModel(cube, program, true); //add and saveAs
        programCache_[cube->getType()] = program; //add program to cache

        std::cout << "... done constructing Program. Cached it." << std::endl;
    }
    else
    { //already in cache
        //std::cout << "Found Program " << value->second->getHandle() << " in cache." << std::endl;
        scene->addModel(cube, value->second, false); //add, already saved
    }
    //std::cout << "... done adding cube" << std::endl;
}
