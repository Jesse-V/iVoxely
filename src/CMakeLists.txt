cmake_minimum_required(VERSION 2.6)

project(ivoxely)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS  "-g -O3 --std=c++11 -Wno-c++98-compat-pedantic -pedantic -Weverything -Wno-unused-parameter -Wno-global-constructors -Wno-exit-time-destructors -Wno-non-virtual-dtor -Wno-weak-vtables -Wno-padded -Wno-cast-align")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS  "-g -O3 --std=c++11 -pedantic -Wall -Wextra -Wdouble-promotion -Wfloat-equal -Wunsafe-loop-optimizations -Wno-unused-parameter")
endif()

include_directories(.)
#link_directories()

add_executable(ivoxely
    main.cpp
    Game/Game.cpp
    Game/Player.cpp
    Game/Voxels/Cube.cpp
    Game/Voxels/Chunk.cpp
    Game/Voxels/Landscape.cpp
    World/Scene.cpp
    World/Camera.cpp
    World/Light.cpp
    Modeling/Mesh/Mesh.cpp
    Modeling/Mesh/PlyParser.cpp
    Modeling/Model.cpp
    Modeling/DataBuffers/VertexBuffer.cpp
    Modeling/DataBuffers/IndexBuffer.cpp
    Modeling/DataBuffers/NormalBuffer.cpp
    Modeling/DataBuffers/SampledBuffers/SampledBuffer.cpp
    Modeling/DataBuffers/SampledBuffers/TextureBuffer.cpp
    Modeling/DataBuffers/SampledBuffers/BumpMap.cpp
    Modeling/DataBuffers/SampledBuffers/CoordinateMapReader.cpp
    Modeling/Shading/ShaderManager.cpp
    Modeling/Shading/ShaderSnippet.cpp
    Modeling/Shading/Program.cpp
    Modeling/Shading/Shader.cpp
)

IF(WIN32)
    target_link_libraries(ivoxely glut glew32 GL png)
ELSE()
    target_link_libraries(ivoxely glut GLEW GL png)
ENDIF()
