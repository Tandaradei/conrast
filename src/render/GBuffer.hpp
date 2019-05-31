#ifndef GBUFFER_HPP
#define GBUFFER_HPP

#include "render/RenderTarget.hpp"
#include "utils/Vec.hpp"
#include "color/Color.hpp"


namespace conrast { namespace render {

class GBuffer
{
public:
    //const float MAX_DEPTH = 1000.0f;
    struct Value {
        color::Color diffuse = color::Color::Black;
        utils::Vec3f normal = { 0.0f, 0.0f, -1.0f };
        float depth = 1000.0f;
    };
    GBuffer(const RenderTarget& renderTarget);
    const Value& getValue(utils::Vec2i position) const;
    Value& getValueMut(utils::Vec2i position);


private:
    const utils::Vec2i m_SIZE;
    std::vector<Value> m_values;
};


}}

#endif // GBUFFER_HPP
