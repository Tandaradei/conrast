#include "ImageSurface.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../external/stb_image_write.h"

namespace conrast { namespace surface {

ImageSurface::ImageSurface(utils::Vec2i resolution, ImageSurface::ImageFormat imageFormat)
	: Surface(resolution),
	m_imageFormat(imageFormat)
{}


void ImageSurface::display(const render::RenderTarget& renderTarget) const {
    std::vector<uint8_t> data;
	const auto size = renderTarget.getSize();
	const utils::Vec2f resolutionScaling = utils::Vec2f{
		static_cast<float>(size.x) / static_cast<float>(m_resolution.x),
		static_cast<float>(size.y) / static_cast<float>(m_resolution.y)
	};

    data.resize(static_cast<size_t>(m_resolution.x * m_resolution.y * 3));
	const auto& pixels = renderTarget.getPixels();
	for (unsigned int y = 0; y < m_resolution.y; y++) {
		for (unsigned int x = 0; x < m_resolution.x; x++) {
			size_t dataIndex = y * m_resolution.x + x;
			size_t pixelIndex = static_cast<size_t>(y * resolutionScaling.y) * size.x + static_cast<size_t>(x * resolutionScaling.x);
			data[dataIndex * 3 + 0] = pixels[pixelIndex].r;
			data[dataIndex * 3 + 1] = pixels[pixelIndex].g;
			data[dataIndex * 3 + 2] = pixels[pixelIndex].b;
		}
	}
	switch (m_imageFormat) {
	case ImageFormat::BMP:
		stbi_write_bmp("render.bmp", m_resolution.x, m_resolution.y, 3, data.data());
		break;
	case ImageFormat::PNG:
		stbi_write_png("render.png", m_resolution.x, m_resolution.y, 3, data.data(), m_resolution.x * 3);
		break;

	}
}

}}
