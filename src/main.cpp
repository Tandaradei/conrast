#include <iostream>

#include "surface/ConsoleSurface.hpp"
#include "rasterizer/Rasterizer.hpp"

constexpr conrast::utils::Vec3f mkVert(const char* txt) {
    return {
        txt[0] == 'L' ? -1.0f : 1.0f,
        txt[1] == 'B' ? -1.0f : 1.0f,
        txt[2] == 'F' ? -1.0f : 1.0f,
    };
}

int main() {
    using namespace conrast;
    surface::ConsoleSurface surface(80, 40);
    color::Color white(255, 255, 255, 255);
    color::Color grey(100, 100, 100, 255);
    rast::Rasterizer rasterizer({
        rast::Rasterizer::Options::FillType::Line,
        rast::Rasterizer::Options::VertexStruct::TriangleStrip
    });

    std::vector<mesh::Vertex> cubeVertices = {
        { mkVert("LTF"), white },
        { mkVert("RTF"), white },
        { mkVert("LBF"), white },
        { mkVert("RBF"), white },
        { mkVert("RBB"), grey },
        { mkVert("RTF"), grey },
        { mkVert("RTB"), grey },
        { mkVert("LTF"), grey },
        { mkVert("LTB"), grey },
        { mkVert("LBF"), grey },
        { mkVert("LBB"), grey },
        { mkVert("RBB"), grey },
        { mkVert("LTB"), grey },
        { mkVert("RTB"), grey }
    };

    auto translateObject = [](std::vector<mesh::Vertex>& vertices, utils::Vec3f translation) {
        for(auto& vertex : vertices) {
            vertex.position.x += translation.x;
            vertex.position.y += translation.y;
            vertex.position.z += translation.z;
        }
    };

    /*
    std::vector<mesh::Vertex> lineVertices = {
        { mkVert("LTF"), white },
        { mkVert("RTF"), white },
        { mkVert("RBF"), white },
        { mkVert("LBF"), white }
    };
    */

    translateObject(cubeVertices, { 0.0f, 0.0f, 2.5f });
    char input = 'q';
    utils::Vec2f translation{ 0.0f, 0.0f };
    do {
        surface.clear(color::Color::Black);
        rasterizer.render(surface, cubeVertices);
        surface.display();

        input = getchar();
        translateObject(cubeVertices, { -translation.x, -translation.y, 0.0f });
        switch(input) {
        case 'a':
            translation.x -= 0.25f;
            break;
        case 'd':
            translation.x += 0.25f;
            break;
        case 'w':
            translation.y += 0.25f;
            break;
        case 's':
            translation.y -= 0.25f;
            break;
        default:
            break;
        }

        translateObject(cubeVertices, { translation.x, translation.y, 0.0f });
    } while(input != 'q');

    return 0;
}
