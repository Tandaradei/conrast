#include <iostream>

#include "surface/ConsoleSurface.hpp"
#include "rasterizer/Rasterizer.hpp"

constexpr conrast::utils::Vec3f mkVert(const char txt[3]) {
    return {
        txt[0] == 'L' ? -1.0f : 1.0f,
        txt[1] == 'B' ? -1.0f : 1.0f,
        txt[2] == 'F' ? -1.0f : 1.0f,
    };
}

int main() {
    using namespace conrast;
    surface::ConsoleSurface surface(100, 50);
    color::Color white { 1.0f, 1.0f, 1.0f, 1.0f };
    color::Color grey { 0.2f, 0.2f, 0.2f, 1.0f };
    rast::Rasterizer rasterizer({
        rast::Rasterizer::Options::FillType::Fill,
        rast::Rasterizer::Options::VertexStruct::TriangleStrip
    });

    mesh::Mesh cube = {
        {
            { mkVert("LTF"), white },
            { mkVert("RTF"), white },
            { mkVert("LBF"), white },
            { mkVert("RBF"), white },
            { mkVert("RBB"), grey },
            { mkVert("RTB"), grey },
            { mkVert("LTB"), grey },
            { mkVert("LBB"), grey },
        },
        { 0, 1, 2, 3, 4, 1, 5, 0, 6, 2, 7, 4, 6, 5 }
    };

    auto translateMesh = [](mesh::Mesh& mesh, utils::Vec3f translation) {
        for(auto& vertex : mesh.vertices) {
            vertex.position.x += translation.x;
            vertex.position.y += translation.y;
            vertex.position.z += translation.z;
        }
    };

    translateMesh(cube, { 0.0f, 0.0f, 2.5f });
    char input = 'q';
    utils::Vec2f translation{ 0.0f, 0.0f };
    do {
        surface.clear(color::Color::Black);
        rasterizer.render(surface, cube);
        surface.display();

        input = getchar();
        translateMesh(cube, { -translation.x, -translation.y, 0.0f });
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

        translateMesh(cube, { translation.x, translation.y, 0.0f });
    } while(input != 'q');

    return 0;
}
