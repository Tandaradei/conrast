#ifndef LINE_HPP
#define LINE_HPP

#include "mesh/Vertex.hpp"

namespace conrast { namespace mesh {

struct Line {
    Vertex start;
    Vertex end;
};

} }

#endif // LINE_HPP
