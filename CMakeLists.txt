cmake_minimum_required(VERSION 3.0)

project(conrast)

set(conrast_VERSION_MAJOR 0)
set(conrast_VERSION_MINOR 1)

SET(BASEPATH "${CMAKE_SOURCE_DIR}/src")
INCLUDE_DIRECTORIES("${BASEPATH}")

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/color/Color.hpp
    src/color/Color.cpp
    src/utils/Vec.hpp
    src/utils/Vec.cpp
    src/utils/Geometry.hpp
    src/utils/Geometry.cpp
    src/surface/Surface.hpp
    src/surface/Surface.cpp
    src/surface/ConsoleSurface.hpp
    src/surface/ConsoleSurface.cpp
    src/rasterizer/Rasterizer.hpp
    src/rasterizer/Rasterizer.cpp
    src/render/RenderTarget.hpp
    src/render/RenderTarget.cpp
    src/render/Renderer.hpp
    src/render/Renderer.cpp
    src/render/GBuffer.hpp
    src/render/GBuffer.cpp
    src/mesh/Vertex.hpp
    src/mesh/Vertex.cpp
    src/mesh/Line.hpp
    src/mesh/Line.cpp
    src/mesh/Triangle.hpp
    src/mesh/Triangle.cpp
    src/mesh/Mesh.hpp
    src/mesh/Mesh.cpp
)
