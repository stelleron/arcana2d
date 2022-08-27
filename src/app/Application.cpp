#include <thread>

#include "utils/Camera.hpp"
#include "utils/Logger.hpp"
#include "time/Timer.hpp"
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
        Timer timer;
        float deltatime_cap;

        // Game loop

        // Init
        app.config(config);
        window.init(config);
        deltatime_cap = 1.0f/config.fps_cap;
        Shader shader(0, 0);
        camera.defaultSettings(config.width, config.height);
        render_ctx.init();
        game_ctx.setWindow(window);
        window.setData(&game_ctx);
        app.init(game_ctx);

        while(!window.shouldClose()) {
            // Reset stuff and poll events
            timer.reset();
            game_ctx.resetEvents();
            window.pollEvents();

            if (window.isActive()) {

                // Update;
                game_ctx.setCamera(camera);
                app.update(game_ctx);

                // Render
                window.fill();
                render_ctx.setCurrentShader(&shader);
                render_ctx.setCurrentCamera(game_ctx.getCamera());
                app.render(render_ctx);
                window.swapBuffer();

                // Put thread to sleep to cap framerate
                if (timer.getElapsed() < deltatime_cap) {
                    float sleepTime = deltatime_cap - timer.getElapsed();
                    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long int>(sleepTime * 1000.0f)));
                }
            }
            game_ctx.setDeltaTime(timer.getElapsed());
            LOG(game_ctx.getFPS());
        }

        app.finish();
    }
}