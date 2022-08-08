#include "gfx/RenderContext.hpp"
#include "utils/DebugOnly.hpp"

namespace arcana {
    // RENDER CONTEXT IMPL.
    RenderContext::RenderContext() {

    }

    RenderContext::~RenderContext() {

    }

    void RenderContext::init() {
        // Initialise the shader
        Shader shader(0, 0);
        default_shader = shader;
    }

    void RenderContext::useDefault() {
        default_shader.use();
    }
}