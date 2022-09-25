// SAMPLE PONG GAME
#include "Arcana2D.hpp"
using namespace arcana;

#define PADDLE_SPEED 5.0f
#define BALL_RADIUS 20.0f
#define RED Color::RGB(255, 0, 0)
#define BLUE Color::RGB(0, 0, 255)
#define WHITE Color::RGB(255, 255, 255)

// Stores the paddle object
struct Paddle {
    Vector2 pos;
    Color color;

    inline DrawQuad getDrawRect() {
        return drawable::make(
            Rectangle(pos, 50, 200),
            color
        );
    }
};

// Stores the ball object
struct Ball {
    Vector2 pos;

    inline DrawCircle getDrawCircle() {
        return drawable::make(
            Circle(pos, BALL_RADIUS), WHITE
        );
    }
};

class PongGame : public Application {

    // Player and enemy paddles
    Paddle playerPaddle;
    Paddle enemyPaddle;
    Ball ball;
    Font font;

    void config(AppConfig& config) {
        config.title = "Pong Demo";
    }

    void init(GameContext& ctx) {
        // Initialise paddles
        playerPaddle.pos = {100.0f, 200.0f};
        playerPaddle.color = BLUE;
        enemyPaddle.pos = {650.0f, 200.0f};
        enemyPaddle.color = RED;
        ball.pos = {400.0f, 300.0f};
        font.load("cache/ThaleahFat.ttf");
    }

    void update(GameContext& ctx) {
        // Move player paddle
        if (ctx.keyboard.isHeld(Up) || ctx.keyboard.isPressed(Up)) {
            playerPaddle.pos.y -= PADDLE_SPEED;
        }
        else if (ctx.keyboard.isHeld(Down) || ctx.keyboard.isPressed(Down)) {
            playerPaddle.pos.y += PADDLE_SPEED;
        }
    }

    void render(RenderContext& ctx) { 
        ctx.draw(playerPaddle.getDrawRect());
        ctx.draw(enemyPaddle.getDrawRect());
        ctx.draw(ball.getDrawCircle());
    }

    void finish() {

    }
};

int main() {  
    PongGame game;
    build(game);
}
