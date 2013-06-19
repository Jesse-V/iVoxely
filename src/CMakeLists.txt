cmake_minimum_required(VERSION 2.6)

project(ivoxely)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS  "-g --std=c++0x -Weverything -Wno-documentation -Wno-c++98-compat-pedantic -Wno-shadow -Wno-cast-align -Wno-padded -Wno-weak-vtables -Wno-non-virtual-dtor -Wno-unknown-pragmas -Wno-unused-parameter")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS  "-g -O2 --std=c++0x -Wall -Wextra -Wdouble-promotion -Wfloat-equal -Wunsafe-loop-optimizations")
endif()

include_directories(. glm)
#link_directories()

# Let's keep this organized and logically sorted
add_executable(ivoxely
    main.cpp
    Game/Game.cpp
    Game/Player.cpp
    World/Scene.cpp
    World/Camera.cpp
    World/Light.cpp
    Models/Ground/Ground.cpp
    Rendering/RenderableObject.cpp
    Rendering/DataBuffers/VertexBuffer.cpp
    Rendering/DataBuffers/IndexBuffer.cpp
    Rendering/DataBuffers/NormalBuffer.cpp
    Rendering/DataBuffers/SampledBuffers/SampledBuffer.cpp
    Rendering/DataBuffers/SampledBuffers/TextureBuffer.cpp
    Rendering/DataBuffers/SampledBuffers/BumpMap.cpp
    Resources/OpenGL/ShaderSnippet.cpp
    Resources/OpenGL/Program.cpp
    Resources/OpenGL/Shader.cpp
)

IF(WIN32)
    target_link_libraries(ivoxely glut glew32 GL)
ELSE()
    target_link_libraries(ivoxely glut GLEW GL)
ENDIF()
