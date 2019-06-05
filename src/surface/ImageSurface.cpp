#include "ImageSurface.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../external/stb_image_write.h"

namespace conrast { namespace surface {

ImageSurface::ImageSurface(uint16_t width, uint16_t height)
    : Surface(width, height)
{}


void ImageSurface::display() const {
    std::vector<uint8_t> data;
    data.resize(static_cast<size_t>(m_SIZE.x * m_SIZE.y * 3));
    for (size_t i = 0; i < m_pixels.size(); i++) {
        data[i * 3 + 0] = m_pixels[i].r;
        data[i * 3 + 1] = m_pixels[i].g;
        data[i * 3 + 2] = m_pixels[i].b;
    }
    stbi_write_bmp("render.bmp", m_SIZE.x, m_SIZE.y, 3, data.data());
}

}}
