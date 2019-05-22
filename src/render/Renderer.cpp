#include "Renderer.hpp"

namespace conrast { namespace render {


void Renderer::render(RenderTarget &renderTarget, const GBuffer &gBuffer) {
    for (int y = 0; y < renderTarget.getSize().y; y++) {
        for (int x = 0; x < renderTarget.getSize().x; x++) {
            const auto& gBufferValue = gBuffer.getValue({ x, y });
            renderTarget.drawPixel({ x, y }, gBufferValue.diffuse);
        }
    }
}

}}

