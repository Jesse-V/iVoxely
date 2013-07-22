
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
            for (int z = 0; z <= 0; z++)
            {
                auto type = Cube::Type::STONE;
                addCube(type, x, y, z, scene);
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



void Landscape::addCube(Cube::Type type, int x, int y, int z,
                        const std::shared_ptr<Scene>& scene
)
{
    auto cube = std::make_shared<Cube>(type, x, y, z);

    auto value = programCache_.find(type);
    if (value == programCache_.end())
    { //not in cache
        auto program = ShaderManager::createProgram(cube,
            scene->getVertexShaderGLSL(), scene->getFragmentShaderGLSL(),
            scene->getLights()
        );

        scene->addModel(cube, program, true); //add and saveAs
        programCache_[type] = program; //add program to cache
    }
    { //already in cache
        scene->addModel(cube, value->second, false); //add, already saved
    }
}
