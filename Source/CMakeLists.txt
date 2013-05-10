cmake_minimum_required(VERSION 2.6)

project(OpenGL_program)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS  "-g --std=c++0x -Weverything -Wno-documentation -Wno-c++98-compat-pedantic -Wno-shadow -Wno-cast-align -Wno-padded -Wno-weak-vtables -Wno-non-virtual-dtor -Wno-unknown-pragmas")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS  "-g -O2 --std=c++0x -Wall -Wextra -Wdouble-promotion -Wfloat-equal -Wunsafe-loop-optimizations")
endif()

include_directories(. glm)
#link_directories()

# Let's keep this organized and logically sorted
add_executable(OpenGL_program
    main.cpp
    Game/Game.cpp
    Game/Player.cpp
    World/Scene.cpp
    World/Camera.cpp
    World/Light.cpp
    CustomObjects/Ground/Ground.cpp
    Modeling/DataBuffers/TextureBuffer.cpp
    Modeling/DataBuffers/VertexBuffer.cpp
    Modeling/RenderableObject.cpp
    Modeling/Mesh.cpp
    Resources/OpenGL/Program.cpp
    Resources/OpenGL/Shader.cpp
)

IF(WIN32)
    target_link_libraries(OpenGL_program glut glew32 GL)
ELSE()
    target_link_libraries(OpenGL_program glut GLEW GL)
ENDIF()
