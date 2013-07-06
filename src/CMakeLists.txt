cmake_minimum_required(VERSION 2.6)

project(ivoxely)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS  "-g -O3 --std=c++0x -Weverything -Wno-documentation -Wno-c++98-compat-pedantic -Wno-shadow -Wno-cast-align -Wno-padded -Wno-weak-vtables -Wno-non-virtual-dtor -Wno-unknown-pragmas -Wno-unused-parameter -Wno-deprecated-register -Werror -L/usr/local/lib -lpng")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS  "-g -O3 --std=c++0x -Wall -Wextra -Wdouble-promotion -Wfloat-equal -Wunsafe-loop-optimizations -Wno-unused-parameter")
endif()

include_directories(. glm)
#link_directories()

add_executable(ivoxely
    main.cpp
    Game/Game.cpp
    Game/Player.cpp
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
