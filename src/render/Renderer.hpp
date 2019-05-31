#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "render/GBuffer.hpp"
#include "render/RenderTarget.hpp"

namespace conrast { namespace render {

class Renderer
{
public:
    void render(RenderTarget& renderTarget, const GBuffer& gBuffer);
};

} }

#endif // RENDERER_HPP
