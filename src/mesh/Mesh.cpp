#include "Mesh.hpp"

namespace conrast { namespace mesh {

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indexes)
    : vertices(vertices),
    indexes(indexes)
{}

}}

