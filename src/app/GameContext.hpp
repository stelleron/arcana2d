#ifndef ARCANA2D_GAME_CONTEXT
    #define ARCANA2D_GAME_CONTEXT

    #include "utils/Camera.hpp"
    namespace arcana {
        // Used to communicate with the application logic
        class GameContext {
            private:
                Camera* curr_camera;
            public:
                // Constructor
                GameContext();
                // Destructor
                ~GameContext();

                // SETTERS
                // =======
                void setCamera(Camera& camera);

                // GETTERS
                // =======
                Camera* getCamera();
        };
    }
#endif