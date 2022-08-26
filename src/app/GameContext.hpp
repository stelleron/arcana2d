#ifndef ARCANA2D_GAME_CONTEXT
    #define ARCANA2D_GAME_CONTEXT

    #include "utils/Camera.hpp"
    #include "input/EventData.hpp"

    namespace arcana {
        // Used to communicate with the application logic
        class GameContext {
            private:
                Camera* curr_camera;
                EventData event_data;
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
                EventData& getEventData();

                // FUNCTIONS
                // =========
                void resetEvents(); // Reset the event data buffer

                inline bool wasWindowResized() {return event_data.windowData.wasResized;}
        };
    }
#endif