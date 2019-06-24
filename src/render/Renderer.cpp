#include "Renderer.hpp"

namespace conrast { namespace render {

static const utils::Vec3f LIGHT_POS = { 0.0f, 1.0f, 0.0f };
static const float LIGHT_RADIUS = 20.0f;

void Renderer::render(RenderTarget &renderTarget, const GBuffer &gBuffer) {
    for (int y = 0; y < renderTarget.getSize().y; y++) {
        for (int x = 0; x < renderTarget.getSize().x; x++) {
            const auto& gBufferValue = gBuffer.getValue({ x, y });
            color::RGB32f diffuse = gBufferValue.diffuse;
            auto toLight = LIGHT_POS - gBufferValue.position;
            float squaredDistanceToLight = toLight.squaredLength();
            color::RGB8 color_out = color::Black;
            if(squaredDistanceToLight < LIGHT_RADIUS * LIGHT_RADIUS) {
                float dot = gBufferValue.normal.dot(toLight.normalized());
                if(dot > 0.0f) {
                    diffuse *= dot;
                    diffuse *= powf(1.0f - (squaredDistanceToLight / (LIGHT_RADIUS * LIGHT_RADIUS)), 3.0f);
                    color_out = diffuse;
                }
            }
            //diffuse *= ((1000.0f - gBufferValue.depth) / 1000.0f);
            renderTarget.drawPixel({ x, y }, color_out );
        }
    }
}

}}

