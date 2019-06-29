#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "render/Framebuffer.hpp"
#include "render/RenderTarget.hpp"

namespace conrast { namespace render {

class Renderer
{
public:
    void render(RenderTarget& renderTarget, const Framebuffer& framebuffer);
};

} }

#endif // RENDERER_HPP
