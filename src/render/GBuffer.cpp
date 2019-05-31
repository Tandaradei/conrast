#include "GBuffer.hpp"

namespace conrast { namespace render {

GBuffer::GBuffer(const RenderTarget& renderTarget)
    : m_SIZE(renderTarget.getSize())
{
    m_values.resize(static_cast<size_t>(m_SIZE.x * m_SIZE.y));
}

const GBuffer::Value& GBuffer::getValue(utils::Vec2i position) const {
    return m_values[static_cast<size_t>(position.y * m_SIZE.x + position.x)];
}


GBuffer::Value& GBuffer::getValueMut(utils::Vec2i position) {
    return m_values[static_cast<size_t>(position.y * m_SIZE.x + position.x)];
}

}}
