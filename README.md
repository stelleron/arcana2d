# Arcana2D - An easy-to-use 2D game framework written in C++ with GLFW/GLAD
Arcana2D is a game framework designed with a simple and easy-to-use API to get started with programming quickly. With a base Application class to start coding from, the framework is built on an encapsulated design approach.

# Basic Template Program
```cpp
#include "Arcana2D.hpp"
using namespace arcana;

class UntitledGame : public Application{

    void config(AppConfig& config) {

    }
    void init(GameContext& ctx) {

    }
    void update(GameContext& ctx) {

    }
    void render(RenderContext& ctx) {
        
    }
    void finish() {
    
    }
};

int main() {
    UntitledGame game;
    build(game);
}
```

# Features
The framework currently supports the current features:

- Custom message logging
- Window creation, customization and events
- Input handling from keyboard and mouse
- Timing functions
- Random number generation
- Customizable and batched rendering
- Sprite and texture drawing
- Font rendering
- Simple audio playing

These features will be coming in future expansions:
- Expanded audio playing
- Gamepad input
- 2D Physics