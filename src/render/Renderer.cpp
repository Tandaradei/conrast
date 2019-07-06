#include "Renderer.hpp"

#include <algorithm>

namespace conrast { namespace render {

void Renderer::render(RenderTarget &renderTarget, const Framebuffer& framebuffer) {
    for (int y = 0; y < renderTarget.getSize().y; y++) {
        for (int x = 0; x < renderTarget.getSize().x; x++) {
			renderTarget.setPixel({ x, y }, framebuffer.getColor({ x, y }));
        }
    }
}

}}