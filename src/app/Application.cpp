#include <thread>
#include "utils/Logger.hpp"
#include "time/Timer.hpp"
#include "camera/Camera.hpp"
#include "window/Window.hpp"
#include "app/Application.hpp"


namespace arcana {
    void build(Application& app) {
        LOG("Arcana2D: Building the application!");

        // Variable declarations
        AppConfig config;
        Timer internalClock;
        Window window;
        Camera defaultCamera;
        GameContext gameCtx;
        float deltatimeCap;

        // Game Loop
        // 1. INIT
        // First fetch an app config
        LOG("Arcana2D: Configuring the application!");
        app.config(config);

        // Then initialise the app based on conifgurations
        deltatimeCap = 1.0f/config.fps_cap;
        window.init(config);
        defaultCamera.setDim(config.width, config.height);
        gameCtx.setWindow(window);
        gameCtx.setCamera(defaultCamera);
        window.setData(&gameCtx);

        // And then set a game context
        LOG("Arcana2D: Initialising the application!");
        app.init(gameCtx);
        int x = 0;

        // 2. UPDATE
        LOG("Arcana2D: Starting game loop!");
        while(!window.shouldClose()) {
            // Check if game loop should be run 
            gameCtx.resetEvents();
            window.pollEvents();

            if (window.isActive()) {
                // Update
                internalClock.reset();
                app.update(gameCtx);
                if(gameCtx.isKeyReleased(Key::Enter)) {
                    LOG("Hello " << x << "!");
                    x++;
                }

                // Render
                window.fill();
                app.render();
                window.swapBuffer();

                // End loop
                // Put thread to sleep to cap framerate
                if (internalClock.getElapsed() < deltatimeCap) {
                    float sleepTime = deltatimeCap - internalClock.getElapsed();
                    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long int>(sleepTime * 1000.0f)));
                }
            }
            gameCtx.setDeltaTime(internalClock.getElapsed());
        }

        // 3. FINISH
        LOG("Arcana2D: Disposing the application!");
        app.finish();
    }
}