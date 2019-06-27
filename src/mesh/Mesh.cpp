#include "Mesh.hpp"

namespace conrast { namespace mesh {

Mesh::Mesh(const std::vector<Vertex>& vertices,
           const std::vector<unsigned int>& indexes,
           const render::FragmentShader& fragShader,
           VertexStruct vertexStruct)
    : vertices(vertices),
    indexes(indexes),
    fragShader(fragShader),
    vertexStruct(vertexStruct)
{}

}}

