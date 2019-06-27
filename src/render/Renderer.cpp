#include "Renderer.hpp"

namespace conrast { namespace render {



void Renderer::render(RenderTarget &renderTarget, const GBuffer &gBuffer) {
    for (int y = 0; y < renderTarget.getSize().y; y++) {
        for (int x = 0; x < renderTarget.getSize().x; x++) {
            /*
            const auto& gBufferValue = gBuffer.getValue({ x, y });
            color::RGB32f diffuse = gBufferValue.diffuse;
            auto toLight = LIGHT_POS - gBufferValue.position;
            float distanceToLight = toLight.length();
            color::RGB8 color_out = color::Black;
            if(distanceToLight < LIGHT_RADIUS) {
                float dot = gBufferValue.normal.dot(toLight.normalized());
                if(dot > 0.0f) {
                    diffuse *= dot;
                    diffuse *= 1.0f - powf((distanceToLight / LIGHT_RADIUS), 3.0f);
                    color_out = diffuse;
                }
            }
            //diffuse *= ((1000.0f - gBufferValue.depth) / 1000.0f);
            */
            renderTarget.drawPixel({ x, y }, gBuffer.getValue({x, y}).diffuse );
        }
    }
}

}}

