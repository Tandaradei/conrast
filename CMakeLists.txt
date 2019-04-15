cmake_minimum_required(VERSION 3.0)

project(conrast)

set(conrast_VERSION_MAJOR 0)
set(conrast_VERSION_MINOR 1)


add_executable(${PROJECT_NAME}
    main.cpp
    Color/Color.hpp
    Color/Color.cpp
    Utils/Vec.hpp
    Utils/Vec.cpp
    Surface/Surface.hpp
    Surface/Surface.cpp
    Surface/ConsoleSurface.hpp
    Surface/ConsoleSurface.cpp
    Rasterizer/Rasterizer.hpp
    Rasterizer/Rasterizer.cpp
    Mesh/Vertex.hpp
    Mesh/Vertex.cpp
    Mesh/Line.hpp
    Mesh/Line.cpp
    Mesh/Triangle.hpp
    Mesh/Triangle.cpp
)
