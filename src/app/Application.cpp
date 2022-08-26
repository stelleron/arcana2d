#include "utils/Camera.hpp"
#include "gfx/Shader.hpp"
#include "gfx/RenderContext.hpp"
#include "window/Window.hpp"

#include "app/AppConfig.hpp"
#include "app/GameContext.hpp"
#include "app/Application.hpp"

namespace arcana {
    void build(Application& app) {
        // Variable declarations
        AppConfig config;
        Window window;
        Camera camera;
        RenderContext render_ctx;
        GameContext game_ctx;

        // Game loop
        app.config(config);
        window.init(config);
        Shader shader(0, 0);
        camera.defaultSettings(config.width, config.height);
        render_ctx.init();
        app.init();

        window.setData(&game_ctx);

        while(!window.shouldClose()) {
            if (window.isActive()) {

                // Update
                window.pollEvents();
                game_ctx.setCamera(camera);
                app.update(game_ctx);

                // Render
                window.fill();
                render_ctx.setCurrentShader(&shader);
                render_ctx.setCurrentCamera(game_ctx.getCamera());
                app.render(render_ctx);
                window.swapBuffer();
            }
        }

        app.finish();
    }
}