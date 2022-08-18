#ifndef ARCANA2D_HPP
    #define ARCANA2D_HPP
    // To be added to external applications
    //=== STD HEADERS
    #include <functional>
    #include <string>
    
    //=== VENDOR HEADERS
    #include <glad/glad.h>
    #include <GLFW/glfw3.h>
    #include <glm/glm.hpp>

    //=== PROJECT HEADERS
    #include "utils/Color.hpp"

    #include "geom/Vertex.hpp"
    #include "geom/Geometry.hpp"
    #include "geom/DrawGeom.hpp"
    #include "geom/VertexBuffer.hpp"

    #include "utils/Camera.hpp"
    #include "window/Window.hpp"

    #include "res/Image.hpp"

    #include "gfx/Shader.hpp"
    #include "gfx/RenderContext.hpp"
    #include "gfx/Sprite.hpp"

    #include "engine/App.hpp"
    #include "engine/EngineConfig.hpp"
#endif