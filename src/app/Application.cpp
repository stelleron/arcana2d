#include "utils/Camera.hpp"
#include "gfx/Shader.hpp"
#include "gfx/RenderContext.hpp"
#include "window/Window.hpp"

#include "app/AppConfig.hpp"
#include "app/Application.hpp"

namespace arcana {
    void build(Application& app) {
        // Variable declarations
        AppConfig config;
        Window window;
        Camera camera;
        RenderContext render_ctx;

        // Game loop
        app.config(config);
        window.init(config);
        Shader shader(0, 0);
        camera.defaultSettings(config.width, config.height);
        render_ctx.init();
        app.init();

        while(!window.shouldClose()) {
            window.pollEvents();
            if (window.isActive()) {
                render_ctx.setCurrentShader(&shader);
                render_ctx.setCurrentCamera(&camera);
                app.update();
                window.fill();
                app.render(render_ctx);
                window.swapBuffer();
            }
        }

        app.finish();
    }
}