#ifndef ARCANA2D_APPLICATION
    #define ARCANA2D_APPLICATION
    namespace arcana {
        class Application {
            // Application virtual functions
            public:
                virtual void config(AppConfig& config) = 0;
                virtual void init(GameContext& ctx) = 0;
                virtual void update(GameContext& ctx) = 0;
                virtual void render(RenderContext& ctx) = 0;
                virtual void finish() = 0;
        };

        void build(Application& app);
    }
#endif