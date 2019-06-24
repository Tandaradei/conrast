#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include "mesh/Vertex.hpp"

namespace conrast { namespace mesh {

class Mesh
{
public:
    enum class VertexStruct {
        /// No connection between vertices
        Points,
        /// Every two vertices describe a line (1st and 2nd; 3rd and 4th; etc.)
        Lines,
        /// Every vertex describes a line with the successor
        LineStrip,
        /// Every three vertices describe a triangle (1st, 2nd and 3rd; 4th, 5th and 6th; etc.)
        Triangles,
        /// Every vertex describes a triangle with 2 successors
        TriangleStrip
    };

public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indexes;
    VertexStruct vertexStruct;

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indexes, VertexStruct vertexStruct = VertexStruct::TriangleStrip);
    //Mesh(const char* file);
};

} }

#endif // MESH_HPP
