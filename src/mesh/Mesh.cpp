#include "Mesh.hpp"

namespace conrast { namespace mesh {

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indexes, VertexStruct vertexStruct)
    : vertices(vertices),
    indexes(indexes),
    vertexStruct(vertexStruct)
{}

}}

