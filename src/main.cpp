#include <iostream>
#include <chrono>

#include "surface/ConsoleSurface.hpp"
#include "surface/ImageSurface.hpp"
#include "rasterizer/Rasterizer.hpp"
#include "render/Renderer.hpp"
#include "utils/Vec.hpp"

static const conrast::utils::Vec3f LIGHT_POS = { -0.5f, -1.0f, 2.75f };
static const float LIGHT_RADIUS = 100.0f;


conrast::color::RGB8 defaultFrag(const conrast::render::FragmentShaderParameters& params) {
    using namespace conrast;
    auto toLight = LIGHT_POS - params.worldPosition;
    float distanceToLight = toLight.length();
    color::RGB8 color_out = color::Black;
    if(distanceToLight < LIGHT_RADIUS) {
        float dot = params.normal.dot(toLight.normalized());
        if(dot > 0.0f) {
            auto color = params.vertexColor;
            color *= dot;
            color *= 1.0f - powf((distanceToLight / LIGHT_RADIUS), 3.0f);
            color_out = color;
        }
    }
    return color_out;
}

conrast::color::RGB8 simpleLighting(const conrast::render::FragmentShaderParameters& params) {
    using namespace conrast;
    auto toLight = LIGHT_POS - params.worldPosition;
    float distanceToLight = toLight.length();
    color::RGB8 color_out = color::Black;
    if(distanceToLight < LIGHT_RADIUS) {
        float dot = params.normal.dot(toLight.normalized());
        if(dot > 0.0f) {
            color_out = params.vertexColor;
        }
    }
    return color_out;
}

conrast::mesh::Vertex mkCubeVert(const char txt[3], conrast::utils::Vec3f size, conrast::color::RGB8 color) {
    return  {
        {
            size.x * (txt[0] == 'L' ? -1.0f : 1.0f),
            size.y * (txt[1] == 'B' ? -1.0f : 1.0f),
            size.z * (txt[2] == 'F' ? -1.0f : 1.0f),
        },
        conrast::utils::Vec3f{
            (txt[0] == 'L' ? -1.0f : 1.0f),
            (txt[1] == 'B' ? -1.0f : 1.0f),
            (txt[2] == 'F' ? -1.0f : 1.0f),
        }.normalized(),
        color
    };
}

conrast::mesh::Mesh mkCube(conrast::utils::Vec3f size, conrast::color::RGB8 color = conrast::color::White) {
    using namespace conrast;
    return mesh::Mesh {
        {
            { mkCubeVert("LTF", size, color) },
            { mkCubeVert("RTF", size, color) },
            { mkCubeVert("LBF", size, color) },
            { mkCubeVert("RBF", size, color) },
            { mkCubeVert("RBB", size, color) },
            { mkCubeVert("RTB", size, color) },
            { mkCubeVert("LTB", size, color) },
            { mkCubeVert("LBB", size, color) },
        },
        { 0, 1, 2, 3, 4, 1, 5, 0, 6, 2, 7, 4, 6, 5 },
        defaultFrag,
        mesh::Mesh::VertexStruct::TriangleStrip
    };
}

int main() {
    using namespace conrast;
    //surface::ConsoleSurface surface(140, 70);
    surface::ImageSurface surface(1280, 720);
    rast::Rasterizer rasterizer(
                surface.getSize(),
                {
                    rast::Rasterizer::Options::FillType::Fill
                }
    );
    render::Renderer renderer;
	render::Framebuffer framebuffer(surface.getSize(), 0.1f, 100.0f);

    mesh::Mesh floor = {
        {
            { { -100.0f, -1.8f, 1.0f }, { 0.0f, 1.0f, 0.0f }, color::Green },
            { { 100.0f, -1.8f, 1.0f }, { 0.0f, 1.0f, 0.0f }, color::Green },
            { { -100.0f, -1.8f, 1000.0f }, { 0.0f, 1.0f, 0.0f }, color::Green },
            { { 100.0f, -1.8f, 1000.0f }, { 0.0f, 1.0f, 0.0f }, color::Green }
        },
        { 0, 1, 2, 3 },
        defaultFrag
    };

    mesh::Mesh bigCube = mkCube({ 1.0f, 1.0f, 1.0f }, color::Red);
    //bigCube.fragShader = simpleLighting;
    mesh::Mesh smallCube = mkCube({ 0.5f, 0.5f, 0.5f }, color::Blue);

    auto translateMesh = [](mesh::Mesh& mesh, utils::Vec3f translation) {
        for(auto& vertex : mesh.vertices) {
            vertex.position += translation;
        }
    };

    translateMesh(bigCube, { -2.0f, -1.5f, 3.0f });
    translateMesh(smallCube, { 1.2f, 0.0f, 2.0f });

    std::string input = "";
	bool shouldQuit = false;
    utils::Vec2f translation{ 0.0f, 0.0f };
    do {
		auto start = std::chrono::system_clock::now();

		framebuffer.clear();
        rasterizer.rasterize(framebuffer, floor);
        rasterizer.rasterize(framebuffer, bigCube);
        rasterizer.rasterize(framebuffer, smallCube);

		surface.clear(color::Black);
        renderer.render(surface, framebuffer);
        surface.display();

		auto end = std::chrono::system_clock::now();
		auto renderTime = end - start;

		std::cout << "Rendering took " << std::chrono::duration_cast<std::chrono::milliseconds>(renderTime).count() << "ms" << std::endl;

		std::cin >> input;
        translateMesh(smallCube, { -translation.x, -translation.y, 0.0f });
		for (auto character : input) {
			switch (character) {
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
			case 'q':
				shouldQuit = true;
				break;
			default:
				break;
			}
		}

        translateMesh(smallCube, { translation.x, translation.y, 0.0f });
    } while(!shouldQuit);

    return 0;
}
