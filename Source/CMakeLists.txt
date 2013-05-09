cmake_minimum_required(VERSION 2.6)

project(OpenGL_program)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS  "-g -O1 --std=c++0x -Weverything -Wno-documentation -Wno-c++98-compat-pedantic -Wno-shadow -Wno-cast-align -Wno-padded -Wno-weak-vtables -Wno-non-virtual-dtor -Wno-unknown-pragmas")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS  "-g -O2 --std=c++0x -Wall -Wextra -Wdouble-promotion -Wfloat-equal -Wunsafe-loop-optimizations")
endif()

include_directories(. parsers glm)
#link_directories()

add_executable(OpenGL_program
    Game/Game.cpp
    main.cpp
    Modeling/DataBuffers/TextureBuffer.cpp
    Modeling/DataBuffers/VertexBuffer.cpp
    ShaderLoader/Program.cpp
    ShaderLoader/Shader.cpp
    Modeling/Mesh.cpp
    World/Scene.cpp
    World/Camera.cpp
    World/Light.cpp
    Modeling/RenderableObject.cpp
    CustomObjects/Ground/Ground.cpp
)

IF(WIN32)
    target_link_libraries(OpenGL_program glut glew32 GL)
ELSE()
    target_link_libraries(OpenGL_program glut GLEW GL)
ENDIF()


