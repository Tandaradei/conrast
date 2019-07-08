#include "Rasterizer.hpp"

#include <algorithm>

#include "utils/Geometry.hpp"

namespace conrast { namespace  rast {


Rasterizer::Rasterizer(utils::Vec2i rasterSize, Rasterizer::Options options, PerspectiveCamera& camera)
	: m_rasterSize(rasterSize),
	m_options(options),
	m_camera(camera)
{}


void Rasterizer::setRasterSize(utils::Vec2i rasterSize) {
	m_rasterSize = rasterSize;
}


void Rasterizer::setOptions(Rasterizer::Options options) {
	m_options = options;
}

void Rasterizer::setCamera(PerspectiveCamera& camera) {
	m_camera = camera;
}


utils::Vec2i Rasterizer::transformScreenToRaster(utils::Vec2f screenPos) const {
	utils::Vec2f halfSize{ static_cast<float>(m_rasterSize.x) * 0.5f, static_cast<float>(m_rasterSize.y) * 0.5f };
	return {
		static_cast<int>(halfSize.x + screenPos.x * halfSize.x),
		static_cast<int>(halfSize.y + screenPos.y * halfSize.y)
	};
}


utils::Vec2f Rasterizer::transformRasterToScreen(utils::Vec2i rasterPos) const {
	utils::Vec2f halfSize{
		static_cast<float>(m_rasterSize.x) * 0.5f,
		static_cast<float>(m_rasterSize.y) * 0.5f
	};
	return {
		(static_cast<float>(rasterPos.x) - halfSize.x) / halfSize.x,
		(static_cast<float>(rasterPos.y) - halfSize.y) / halfSize.y
	};
}


utils::Vec3f Rasterizer::transformWorldToScreen(utils::Vec3f position) const {
	return m_camera.projectToScreen(position);
	/*{
		position.x / position.z / m_camera.imagePlaneHorizontalSize,
		-position.y / position.z / m_camera.imagePlaneVerticalSize,
		position.z
	};
	*/
}


utils::Vec3f Rasterizer::transformScreenToWorld(utils::Vec3f screenPos) const {
	return m_camera.projectToWorld(screenPos);
	/*{
		screenPos.x * screenPos.z * m_camera.imagePlaneHorizontalSize,
		-screenPos.y * screenPos.z * m_camera.imagePlaneVerticalSize,
		screenPos.z
	};*/
}


void Rasterizer::rasterize(render::Framebuffer& framebuffer, const mesh::Mesh& mesh) const {
	switch (mesh.vertexStruct) {
	case mesh::Mesh::VertexStruct::Points: {
		for (const auto& index : mesh.indexes) {
			const auto& vertex = mesh.vertices[index];
			if (vertex.position.z >= 1.0f) {
				auto posScreen = transformWorldToScreen(vertex.position);
				if (posScreen.x >= -1.0f && posScreen.x <= 1.0f
					&& posScreen.y >= -1.0f && posScreen.y <= 1.0f) {
					auto rasterPos = transformScreenToRaster({ posScreen.x, posScreen.y });
					if (framebuffer.updateDepth(rasterPos, posScreen.z)) {
						framebuffer.setColor(rasterPos, vertex.color);
					}
				}
			}
		}
		break;
	}
	case mesh::Mesh::VertexStruct::Lines: {
		if (mesh.indexes.size() < 2 || mesh.indexes.size() % 2 != 0) {
			return;
		}
		for (auto it = mesh.indexes.begin(); it != mesh.indexes.cend(); ) {
			drawLine(framebuffer, { mesh.vertices[*it++], mesh.vertices[*it++] });
		}
		break;
	}
	case mesh::Mesh::VertexStruct::LineStrip: {
		if (mesh.indexes.size() < 2) {
			return;
		}
		for (auto it = mesh.indexes.begin() + 1; it != mesh.indexes.cend(); it++) {
			drawLine(framebuffer, { mesh.vertices[*(it - 1)], mesh.vertices[*it] });
		}
		break;
	}
	case mesh::Mesh::VertexStruct::Triangles: {
		if (mesh.indexes.size() < 3 || mesh.indexes.size() % 3 != 0) {
			return;
		}
		if (m_options.fillType == Options::FillType::Fill) {
			for (auto it = mesh.indexes.begin(); it != mesh.indexes.cend(); ) {
				drawTriangleFilled(framebuffer, mesh.fragShader, { mesh.vertices[*it++], mesh.vertices[*it++], mesh.vertices[*it++] });
			}
		}
		else if (m_options.fillType == Options::FillType::Line) {
			for (auto it = mesh.indexes.begin(); it != mesh.indexes.cend(); ) {
				drawTriangleLines(framebuffer, { mesh.vertices[*it++], mesh.vertices[*it++], mesh.vertices[*it++] });
			}
		}
		break;
	}
	case mesh::Mesh::VertexStruct::TriangleStrip: {
		if (mesh.indexes.size() < 3) {
			return;
		}
		mesh::Triangle triangle = {
			mesh.vertices[mesh.indexes[0]],
			mesh.vertices[mesh.indexes[1]],
			mesh.vertices[mesh.indexes[2]]
		};
		if (m_options.fillType == Options::FillType::Fill) {
			for (auto it = mesh.indexes.begin() + 3; it != mesh.indexes.cend(); it++) {
				drawTriangleFilled(framebuffer, mesh.fragShader, triangle);
				triangle.vertices[0] = triangle.vertices[1];
				triangle.vertices[1] = triangle.vertices[2];
				triangle.vertices[2] = mesh.vertices[*it];
			}
		}
		else if (m_options.fillType == Options::FillType::Line) {
			for (auto it = mesh.indexes.begin() + 3; it != mesh.indexes.cend(); it++) {
				drawTriangleLines(framebuffer, triangle);
				triangle.vertices[0] = triangle.vertices[1];
				triangle.vertices[1] = triangle.vertices[2];
				triangle.vertices[2] = mesh.vertices[*it];
			}
		}
		break;
	}
	}

}




void Rasterizer::drawLine(render::Framebuffer& framebuffer, const mesh::Line& line) const {
	const utils::Vec3f startScreen = transformWorldToScreen(line.start.position);
	const utils::Vec3f endScreen = transformWorldToScreen(line.end.position);
	const utils::Vec2i startRaster = transformScreenToRaster({ startScreen.x, startScreen.y });
	const utils::Vec2i endRaster = transformScreenToRaster({ endScreen.x, endScreen.y });
	const utils::Vec2i startToEnd = endRaster - startRaster;
	const float length = startToEnd.length();
	const utils::Vec2f dir = utils::Vec2f{ static_cast<float>(startToEnd.x), static_cast<float>(startToEnd.y) } / length;
	const utils::Vec2f startRasterFloat = utils::Vec2f{ static_cast<float>(startRaster.x), static_cast<float>(startRaster.y) };
	for (float i = 0.0f; i <= length; i += 1.0f) {
		auto rasterPos = utils::Vec2i{ static_cast<int>(startRasterFloat.x + i * dir.x), static_cast<int>(startRasterFloat.y + i * dir.y) };
		if (rasterPos.x < 0 || rasterPos.x >= m_rasterSize.x || rasterPos.y < 0 || rasterPos.y >= m_rasterSize.y) {
			continue;
		}
		// TODO interpolate depth and color
		if (framebuffer.updateDepth(rasterPos, startScreen.z)) {
			framebuffer.setColor(rasterPos, line.start.color);
		}
	}
}


void Rasterizer::drawTriangleFilled(render::Framebuffer& framebuffer, const render::FragmentShader& fragShader, const mesh::Triangle& triangle) const {
	const auto as = transformWorldToScreen(triangle.vertices[0].position);
	const auto bs = transformWorldToScreen(triangle.vertices[1].position);
	const auto cs = transformWorldToScreen(triangle.vertices[2].position);

	std::vector<utils::Vec2i> rasterTriangleSorted = {
		transformScreenToRaster(as),
		transformScreenToRaster(bs),
		transformScreenToRaster(cs)
	};

	std::sort(begin(rasterTriangleSorted),
		end(rasterTriangleSorted),
		[](const auto& a, const auto& b) {
			return a.y < b.y;
		}
	);

	auto interpolateX = [](auto start, auto end, int value) {
		return start.x + static_cast<int>(
			std::roundf(
				static_cast<float>(end.x - start.x) *
				(static_cast<float>(value - start.y) / static_cast<float>(end.y - start.y))
			)
			);
	};

	auto clamp = [](int value, int min, int max) {
		if (value < min) return min;
		if (value > max) return max;
		return value;
	};

	auto drawPixel = [&](const utils::Vec3f& a, const utils::Vec3f& b, const utils::Vec3f& c, utils::Vec2i rasterPos) {
		const utils::Vec2f screenPoint2D = transformRasterToScreen(rasterPos);
		const utils::Vec3f ws = utils::geometry::calc2DBarycentric(a, b, c, screenPoint2D);
		const float z = 1.0f /
			((1.0f / a.z) * ws.x +
			(1.0f / b.z) * ws.y +
			(1.0f / c.z) * ws.z);
		// Early Z-Test
		if (framebuffer.isSavedNearer(rasterPos, z)) {
			return;
		}
		const utils::Vec3f p = transformScreenToWorld({ screenPoint2D.x, screenPoint2D.y, z });
		const utils::Vec3f ww = utils::geometry::calc3DBarycentric(
			triangle.vertices[0].position,
			triangle.vertices[1].position,
			triangle.vertices[2].position,
			p);

		const color::RGB32f vertexColor =
			color::RGB32f{ triangle.vertices[0].color } * ww.x +
			color::RGB32f{ triangle.vertices[1].color } * ww.y +
			color::RGB32f{ triangle.vertices[2].color } * ww.z;

		const utils::Vec3f normal = utils::Vec3f(
			triangle.vertices[0].normal * ww.x +
			triangle.vertices[1].normal * ww.y +
			triangle.vertices[2].normal * ww.z).normalize();

		const color::RGB8 outColor = fragShader({
				utils::Vec2f{ screenPoint2D.x + 1.0f, screenPoint2D.y + 1.0f } * 0.5f,
				vertexColor,
				p,
				normal
			});

		if (framebuffer.updateDepth(rasterPos, z)) {
			framebuffer.setColor(rasterPos, outColor);
		}
	};


	// Upper part
	int yStart = clamp(rasterTriangleSorted[0].y, 0, m_rasterSize.y);
	int yEnd = clamp(rasterTriangleSorted[1].y, 0, m_rasterSize.y);
	for (int y = yStart; y < yEnd; y++) {
		int xStart = interpolateX(rasterTriangleSorted[0], rasterTriangleSorted[2], y);
		int xEnd = interpolateX(rasterTriangleSorted[0], rasterTriangleSorted[1], y);
		if (xStart > xEnd) {
			std::swap(xStart, xEnd);
		}
		xStart = clamp(xStart, 0, m_rasterSize.x - 1);
		xEnd = clamp(xEnd, 0, m_rasterSize.x - 1);
		for (int x = xStart; x < xEnd; x++) {
			drawPixel(as, bs, cs, { x, y });
		}
	}
	// Lower part
	yStart = clamp(rasterTriangleSorted[1].y, 0, m_rasterSize.y);
	yEnd = clamp(rasterTriangleSorted[2].y, 0, m_rasterSize.y);
	for (int y = yStart; y < yEnd; y++) {
		int xStart = interpolateX(rasterTriangleSorted[0], rasterTriangleSorted[2], y);
		int xEnd = interpolateX(rasterTriangleSorted[1], rasterTriangleSorted[2], y);
		if (xStart > xEnd) {
			std::swap(xStart, xEnd);
		}
		xStart = clamp(xStart, 0, m_rasterSize.x - 1);
		xEnd = clamp(xEnd, 0, m_rasterSize.x - 1);
		for (int x = xStart; x < xEnd; x++) {
			drawPixel(as, bs, cs, { x, y });
		}
	}
}


void Rasterizer::drawTriangleLines(render::Framebuffer& framebuffer, const mesh::Triangle& triangle) const {
	drawLine(framebuffer, { triangle.vertices[0], triangle.vertices[1] });
	drawLine(framebuffer, { triangle.vertices[1], triangle.vertices[2] });
	drawLine(framebuffer, { triangle.vertices[2], triangle.vertices[0] });
}
} }
