#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include "mesh/Vertex.hpp"

namespace conrast { namespace mesh {

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indexes;

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indexes);
    //Mesh(const char* file);
};

} }

#endif // MESH_HPP
