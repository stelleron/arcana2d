// SAMPLE PONG GAME
#include "Arcana2D.hpp"
using namespace arcana;

#define PADDLE_SPEED 5.0f
#define BALL_RADIUS 10.0f
#define DISTANCE_FROM_END 50.0f
#define PADDLE_SIZE 20
 
#define RED Color::RGB(255, 0, 0)
#define BLUE Color::RGB(0, 0, 255)
#define WHITE Color::RGB(255, 255, 255)

// Stores the scoreboard
struct Scoreboard {
    Texture score_nums;
    int player_score;
    int enemy_score;

    void load() {
        score_nums.load("/Users/donti/Desktop/arcana2d/cache/numbers.png");
        player_score = 0;
        enemy_score = 0;
    }

    void drawScoreboard(RenderContext& ctx) {
        // First the player score
        ctx.draw(score_nums);
        // Then the dash in between

        // Finally the enemy score
    }
};

// Stores the paddle object
struct Paddle {
    Vector2 pos;
    Color color;

    inline DrawQuad getDrawRect() {
        return drawable::make(
            Rectangle(pos, PADDLE_SIZE, 200),
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
    Scoreboard board;
    Ball ball;
    Font font;

    void config(AppConfig& config) {
        config.title = "Pong Demo";
    }

    void init(GameContext& ctx) {
        // Initialise paddles
        playerPaddle.pos = {DISTANCE_FROM_END, 200.0f};
        playerPaddle.color = WHITE;
        enemyPaddle.pos = {800.0f - DISTANCE_FROM_END - PADDLE_SIZE, 200.0f};
        enemyPaddle.color = WHITE;
        ball.pos = {400.0f, 300.0f};
        board.load();
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
        ctx.draw(board.score_nums, {0.0, 0.0}, {10.0, 10.0});
    }

    void finish() {

    }
};

int main() {  
    PongGame game;
    build(game);
}
