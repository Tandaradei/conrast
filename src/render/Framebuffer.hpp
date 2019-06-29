#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <vector>
#include "utils/Vec.hpp"
#include "color/Color.hpp"


namespace conrast { namespace render {

class Framebuffer
{
public:
	Framebuffer(const utils::Vec2i size, const float near, const float far);

	color::RGB8 getColor(utils::Vec2i position) const;
	void setColor(utils::Vec2i position, color::RGB8 color);
	color::RGB8* getColorData(utils::Vec2i position = { 0, 0 });

	// Returned depth is between -1 (near) and 1(far)
	float getDepthNormalized(utils::Vec2i position) const;
	// depth must be between -1 (near) and 1(far)
	void setDepthNormalized(utils::Vec2i position, float depth);
	// Returns true if passed depth is nearer than saved depth and update saved depth with passed depth
	bool updateDepth(utils::Vec2i position, float depth);
	// depth must be between -1 (near) and 1(far)
	// Returns true if passed depth is nearer than saved depth and update saved depth with passed depth
	bool updateDepthNormalized(utils::Vec2i position, float depth);

	bool isSavedNearer(utils::Vec2i position, float depth) const;
	float* getDepthData(utils::Vec2i position = { 0, 0 });

	float normalizeDepth(float depth) const;

	void clear(color::RGB8 color = color::Black, float depth = 1.0f);

private:
	const utils::Vec2i			m_SIZE;
	const float					m_near;
	const float					m_far;
	const float					m_depthTransformSummand;
	const float					m_depthTransformFactor;
	std::vector<color::RGB8>	m_color;
	std::vector<float>			m_depth;
};

} }

#endif // FRAMEBUFFER_HPP
