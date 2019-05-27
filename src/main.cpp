#include <iostream>

#include "surface/ConsoleSurface.hpp"
#include "surface/ImageSurface.hpp"
#include "rasterizer/Rasterizer.hpp"
#include "render/Renderer.hpp"
#include "utils/Vec.hpp"

constexpr conrast::utils::Vec3f mkCubeVert(const char txt[3], conrast::utils::Vec3f size) {
    return {
        size.x * (txt[0] == 'L' ? -1.0f : 1.0f),
        size.y * (txt[1] == 'B' ? -1.0f : 1.0f),
        size.z * (txt[2] == 'F' ? -1.0f : 1.0f),
    };
}

conrast::mesh::Mesh mkCube(conrast::utils::Vec3f size, conrast::color::Color color = conrast::color::Color::White) {
    using namespace conrast;
    return mesh::Mesh {
        {
            { mkCubeVert("LTF", size), color },
            { mkCubeVert("RTF", size), color },
            { mkCubeVert("LBF", size), color },
            { mkCubeVert("RBF", size), color },
            { mkCubeVert("RBB", size), color },
            { mkCubeVert("RTB", size), color },
            { mkCubeVert("LTB", size), color },
            { mkCubeVert("LBB", size), color },
        },
        { 0, 1, 2, 3, 4, 1, 5, 0, 6, 2, 7, 4, 6, 5 }
    };
}

int main() {
    using namespace conrast;
    //surface::ConsoleSurface surface(100, 50);
    surface::ImageSurface surface(800, 800);
    rast::Rasterizer rasterizer(
                surface.getSize(),
                {
                    rast::Rasterizer::Options::FillType::Fill,
                    rast::Rasterizer::Options::VertexStruct::TriangleStrip
                }
    );
    render::Renderer renderer;

    mesh::Mesh floor = {
        {
            { { -100.0f, -1.8f, 1.0f }, color::Color::Green },
            { { 100.0f, -1.8f, 1.0f }, color::Color::Green },
            { { -100.0f, -1.8f, 1000.0f }, color::Color::Green },
            { { 100.0f, -1.8f, 1000.0f }, color::Color::Green }
        },
        { 0, 1, 2, 3 }
    };
    mesh::Mesh bigCube = mkCube({ 1.0f, 1.0f, 1.0f }, color::Color::Red);
    mesh::Mesh smallCube = mkCube({ 0.5f, 0.5f, 0.5f }, color::Color::Blue);

    auto translateMesh = [](mesh::Mesh& mesh, utils::Vec3f translation) {
        for(auto& vertex : mesh.vertices) {
            vertex.position.x += translation.x;
            vertex.position.y += translation.y;
            vertex.position.z += translation.z;
        }
    };

    translateMesh(bigCube, { -2.0f, -1.5f, 3.0f });
    translateMesh(smallCube, { 1.2f, 0.0f, 2.0f });

    char input = 'q';
    utils::Vec2f translation{ 0.0f, 0.0f };
    do {
        surface.clear(color::Color::Black);
        render::GBuffer gBuffer(surface);
        rasterizer.fillGBuffer(gBuffer, floor);
        rasterizer.fillGBuffer(gBuffer, bigCube);
        rasterizer.fillGBuffer(gBuffer, smallCube);
        renderer.render(surface, gBuffer);
        surface.display();

        input = getchar();
        translateMesh(smallCube, { -translation.x, -translation.y, 0.0f });
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

        translateMesh(smallCube, { translation.x, translation.y, 0.0f });
    } while(input != 'q');

    return 0;
}
