#include <iostream>
#include <chrono>

#include "surface/ConsoleSurface.hpp"
#include "surface/ImageSurface.hpp"
#include "rasterizer/PerspectiveCamera.hpp"
#include "rasterizer/Rasterizer.hpp"
#include "render/Renderer.hpp"
#include "render/RenderTarget.hpp"
#include "utils/Vec.hpp"

static const conrast::utils::Vec3f LIGHT_POS = { -0.5f, 1.0f, 1.75f };
static const float LIGHT_RADIUS = 100.0f;
static const float RES = 2.0f;


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
			float lightFactor = (distanceToLight / LIGHT_RADIUS);
			color *= 1.0f - lightFactor * lightFactor * lightFactor;
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
            0.5f * size.x * (txt[0] == 'L' ? -1.0f : 1.0f),
			0.5f * size.y * (txt[1] == 'B' ? -1.0f : 1.0f),
			0.5f * size.z * (txt[2] == 'F' ? -1.0f : 1.0f),
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
	render::RenderTarget resultImage(1280, 720);

	surface::ConsoleSurface consoleSurface({ 120, 40 });
	surface::ImageSurface imageSurface({ 1280, 720 }, surface::ImageSurface::ImageFormat::BMP);
	
	utils::Vec3f camPos{ 0.0f, 0.0f, 0.0f };
	float fov = 90.0f;
	rast::PerspectiveCamera cam;
	cam.setValues(
		camPos,
		{ 0.0f, 0.0f, 1.0f },
		0.1f,
		100.0f,
		fov,
		9.0f / 16.0f
	);

    rast::Rasterizer rasterizer(
		resultImage.getSize(),
        { rast::Rasterizer::Options::FillType::Fill },
		cam
    );

    render::Renderer renderer;
	render::Framebuffer framebuffer(resultImage.getSize(), 0.5f, 1000.0f);

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

    mesh::Mesh bigCube = mkCube({ 2.0f, 2.0f, 2.0f }, color::Red);
    //bigCube.fragShader = simpleLighting;
    mesh::Mesh smallCube = mkCube({ 1.0f, 1.0f, 1.0f }, color::Blue);

    auto translateMesh = [](mesh::Mesh& mesh, utils::Vec3f translation) {
        for(auto& vertex : mesh.vertices) {
            vertex.position += translation;
        }
    };

    translateMesh(bigCube, { -2.0f, -1.5f, 3.0f });
    translateMesh(smallCube, { 1.2f, 0.0f, 2.0f });

    std::string input = "";
	bool shouldQuit = false;
    do {
		auto renderStart = std::chrono::system_clock::now();

		framebuffer.clear();
        rasterizer.rasterize(framebuffer, bigCube);
        rasterizer.rasterize(framebuffer, smallCube);
		rasterizer.rasterize(framebuffer, floor);

		//resultImage.clear(color::Black);
        renderer.render(resultImage, framebuffer);

		auto renderEnd = std::chrono::system_clock::now();
		auto renderTime = renderEnd - renderStart;

		auto displayConsoleStart = std::chrono::system_clock::now();
		consoleSurface.display(resultImage);
		auto displayConsoleEnd = std::chrono::system_clock::now();
		auto displayConsoleTime = displayConsoleEnd - displayConsoleStart;

		auto displayImageStart = std::chrono::system_clock::now();
		imageSurface.display(resultImage);
		auto displayImageEnd = std::chrono::system_clock::now();
		auto displayImageTime = displayImageEnd - displayImageStart;

		std::cout << "Rendering(" << resultImage.getSize().x << ", " << resultImage.getSize().y << ") took " << std::chrono::duration_cast<std::chrono::milliseconds>(renderTime).count() << "ms\n";
		std::cout << "Displaying on console(" << consoleSurface.getResolution().x << ", " << consoleSurface.getResolution().y << ") took " << std::chrono::duration_cast<std::chrono::milliseconds>(displayConsoleTime).count() << "ms\n";
		std::cout << "Displaying on image(" << imageSurface.getResolution().x << ", " << imageSurface.getResolution().y << ") took " << std::chrono::duration_cast<std::chrono::milliseconds>(displayImageTime).count() << "ms\n";

		std::cin >> input;
		for (auto character : input) {
			switch (character) {
			case 'a':
				camPos.x -= 0.25f;
				break;
			case 'd':
				camPos.x += 0.25f;
				break;
			case 'w':
				camPos.z += 0.25f;
				break;
			case 's':
				camPos.z -= 0.25f;
				break;
			case '+':
				fov -= 5.0f;
				break;
			case '-':
				fov += 5.0f;
				break;
			case 'q':
				shouldQuit = true;
				break;
			default:
				break;
			}
		}
		cam.setValues(
			camPos,
			{ 0.0f, 0.0f, 1.0f },
			0.1f,
			100.0f,
			fov,
			9.0f / 16.0f
		);
    } while(!shouldQuit);

    return 0;
}
