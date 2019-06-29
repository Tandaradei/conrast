#include "Framebuffer.hpp"

namespace conrast { namespace render {

#define SIZE_T(x) static_cast<size_t>(x)

Framebuffer::Framebuffer(const utils::Vec2i size, const float near, const float far) :
m_SIZE(size),
m_near(near),
m_far(far),
m_depthTransformSummand((far + near) /(far - near)),
m_depthTransformFactor((-2.0f * far * near) / (far - near)){
	m_color.resize(SIZE_T(size.x) * SIZE_T(size.y), color::Black);
	m_depth.resize(SIZE_T(size.x) * SIZE_T(size.y), 1.0f);
}


color::RGB8 Framebuffer::getColor(const utils::Vec2i position) const {
	return m_color[SIZE_T(position.y) * SIZE_T(m_SIZE.x) + SIZE_T(position.x)];
}


void Framebuffer::setColor(const utils::Vec2i position, color::RGB8 color) {
	m_color[SIZE_T(position.y) * SIZE_T(m_SIZE.x) + SIZE_T(position.x)] = color;
}

color::RGB8* Framebuffer::getColorData(const utils::Vec2i position) {
	return &m_color[SIZE_T(position.y) * SIZE_T(m_SIZE.x) + SIZE_T(position.x)];
}


float Framebuffer::getDepthNormalized(const utils::Vec2i position) const {
	return m_depth[SIZE_T(position.y) * SIZE_T(m_SIZE.x) + SIZE_T(position.x)];
}


void Framebuffer::setDepthNormalized(const utils::Vec2i position, float depth) {
	m_depth[SIZE_T(position.y) * SIZE_T(m_SIZE.x) + SIZE_T(position.x)] = depth;
}

bool Framebuffer::updateDepth(const utils::Vec2i position, float depth) {
	return updateDepthNormalized(position, normalizeDepth(depth));
}

bool Framebuffer::updateDepthNormalized(const utils::Vec2i position, float depth) {
	float savedDepth = m_depth[SIZE_T(position.y) * SIZE_T(m_SIZE.x) + SIZE_T(position.x)];
	if (depth < savedDepth) {
		m_depth[SIZE_T(position.y) * SIZE_T(m_SIZE.x) + SIZE_T(position.x)] = depth;
		return true;
	}
	return false;
}

float Framebuffer::normalizeDepth(float depth) const {
	return m_depthTransformSummand + (1.0f / depth) * m_depthTransformFactor;
}

bool Framebuffer::isSavedNearer(const utils::Vec2i position, float depth) const {
	return normalizeDepth(depth) > m_depth[SIZE_T(position.y) * SIZE_T(m_SIZE.x) + SIZE_T(position.x)];
}

float* Framebuffer::getDepthData(const utils::Vec2i position) {
	return &m_depth[SIZE_T(position.y) * SIZE_T(m_SIZE.x) + SIZE_T(position.x)];
}


void Framebuffer::clear(color::RGB8 color, float depth) {
	for (auto& color : m_color) {
		color = color::Black;
	}
	for (auto& depth : m_depth) {
		depth = 1.0f;
	}
}

} }