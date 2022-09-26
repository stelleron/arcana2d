// SAMPLE PONG GAME
#include "Arcana2D.hpp"
using namespace arcana;

#define PADDLE_SPEED 500.0f
#define BALL_SPEED 500.0f

#define BALL_RADIUS 10.0f
#define DISTANCE_FROM_END 20.0f
#define PADDLE_SIZE 20
 
#define FONT_SCALE {4.0, 4.0}

#define RED Color::RGB(255, 0, 0)
#define BLUE Color::RGB(0, 0, 255)
#define WHITE Color::RGB(255, 255, 255)
#define BLACK Color::RGB(0, 0, 0)

// Stores the scoreboard
struct Scoreboard {
    Texture score_nums;
    int playerOne_score;
    int playerTwo_score;

    void load() {
        score_nums.load("/Users/donti/Desktop/arcana2d/cache/numbers.png");
        playerOne_score = 0;
        playerTwo_score = 0;
    }

    void draw(RenderContext& ctx) {
        // First the playerOne score
        ctx.draw(score_nums, Rectangle({8.0f * (round(playerOne_score / 10)), 0.0f}, 8.0f, 8.0f), {317.0, 10.0}, FONT_SCALE);
        ctx.draw(score_nums, Rectangle({8.0f * (playerOne_score % 10), 0.0f}, 8.0f, 8.0f), {350.0, 10.0}, FONT_SCALE);
        // Then the dash in between
        ctx.draw(Rectangle({390.0, 25.0}, 20.0, 5.0));
        // Finally the playerTwo score
        ctx.draw(score_nums, Rectangle({8.0f * (round(playerTwo_score / 10)), 0.0f}, 8.0f, 8.0f), {418.0, 10.0}, FONT_SCALE);
        ctx.draw(score_nums, Rectangle({8.0f * (playerTwo_score % 10), 0.0f}, 8.0f, 8.0f), {451.0, 10.0}, FONT_SCALE);
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
    float angle;

    void start() {
        pos = {400.0f, 300.0f};
        angle = 0;
    }

    void enable() {
        angle = 270 - (random::generate() * 90 - 45); 
    }

    void disable() {
        angle = 0;
    }

    void update(float dt) {
        if (angle != 0) {
            pos.x += sinf(glm::radians(angle)) * dt * BALL_SPEED;
            pos.y -= cosf(glm::radians(angle)) * dt * BALL_SPEED;
            // If position out of bounds, reflect it
            if (pos.y < BALL_RADIUS) {
                angle = angle - 270;
                angle = 270 - angle;
                pos.y = BALL_RADIUS;
            }
            else if (pos.y > 600.0 - BALL_RADIUS) {
                angle = 270 - angle;
                angle = 270 + angle;
                pos.y = 600 - BALL_RADIUS;
            }
        }
    }

    void draw(RenderContext& ctx) {
        ctx.draw(
            drawable::make(
            Circle(pos, BALL_RADIUS), WHITE
            )
        );
        ctx.draw(
            drawable::make(
            Circle(pos, BALL_RADIUS + 4), BLACK, -1
            )
        );
    }
};

struct GoMessage {
    Sprite sprite;
    int tickdown;

    void load() {
        sprite.load("cache/go-message.png");
        sprite.pos = {400.0, 550.0};
        sprite.scale = {3.0, 3.0};
        tickdown = 0;
    }

    void enable() {
        tickdown = 60;
    }

    void draw(RenderContext& ctx) {
        if (tickdown > 0) {
            ctx.draw(sprite);
            this->tickdown--;
        }
    }
};

class PongGame : public Application {

    // Player 1 and Player 2 paddles
    Paddle playerOnePaddle;
    Paddle playerTwoPaddle;
    Scoreboard board;
    Ball ball;
    bool isPlaying;
    bool wasPreviouslyPlaying;
    GoMessage go;
    int counter = 0;

    void config(AppConfig& config) {
        config.title = "Pong Demo";
        config.background_color = Color::RGB(40, 40, 40);
    }

    void init(GameContext& ctx) {
        // Initialise paddles
        playerOnePaddle.pos = {DISTANCE_FROM_END, 200.0f};
        playerOnePaddle.color = WHITE;
        playerTwoPaddle.pos = {800.0f - DISTANCE_FROM_END - PADDLE_SIZE, 200.0f};
        playerTwoPaddle.color = WHITE;
        ball.start();
        board.load();
        wasPreviouslyPlaying = false;
        isPlaying = false;
        go.load();
    }

    void update(GameContext& ctx) {
        // Move Player 1 paddle
        float dy = PADDLE_SPEED * ctx.timer.dt();
        if (ctx.keyboard.isHeld(W) || ctx.keyboard.isPressed(W)) {
            if (playerOnePaddle.pos.y - dy > 0.0f)
                playerOnePaddle.pos.y -= dy;
            else 
                playerOnePaddle.pos.y = 0.0f;
        }
        else if (ctx.keyboard.isHeld(S) || ctx.keyboard.isPressed(S)) {
            if (playerOnePaddle.pos.y + dy < 400.0f)
                playerOnePaddle.pos.y += dy;
            else 
                playerOnePaddle.pos.y = 400.0f;
        }
        // Move Player 2 paddle
        if (ctx.keyboard.isHeld(Up) || ctx.keyboard.isPressed(Up)) {
            if (playerTwoPaddle.pos.y - dy > 0.0f)
                playerTwoPaddle.pos.y -= dy;
            else 
                playerTwoPaddle.pos.y = 0.0f;
        }
        else if (ctx.keyboard.isHeld(Down) || ctx.keyboard.isPressed(Down)) {
            if (playerTwoPaddle.pos.y + dy < 400.0f)
                playerTwoPaddle.pos.y += dy;
            else 
                playerTwoPaddle.pos.y = 400.0f;
        }
        // When player presses enter, game plays
        if (ctx.keyboard.isPressed(Enter)) {
            isPlaying = true;
        }
        // When the game starts playing, add a temporary effect
        if (isPlaying && !wasPreviouslyPlaying) {
            go.enable();
            ball.start();
            ball.enable();
        }

        // Update the ball
        ball.update(ctx.timer.dt());
        wasPreviouslyPlaying = isPlaying;

        // If the ball has passed either boundary, reset and increment score
        if (ball.pos.x < 0.0) {
            ball.disable();
            ball.start();
            isPlaying = false;
            board.playerTwo_score += 1;
        }
        if (ball.pos.x > 800.0) {
            ball.disable();
            ball.start();
            isPlaying = false;
            board.playerOne_score += 1;
        }

        // Also check for collisions between the ball and paddle
        if (playerOnePaddle.pos.y - BALL_RADIUS <= ball.pos.y && playerOnePaddle.pos.y + 200 + BALL_RADIUS >= ball.pos.y) {
            if (abs(playerOnePaddle.pos.x + PADDLE_SIZE - BALL_RADIUS - ball.pos.x) < 5) {
                ball.angle = ball.angle - 180;
                ball.angle = 180 - ball.angle;
            }
        }
        if (playerTwoPaddle.pos.y - BALL_RADIUS <= ball.pos.y && playerTwoPaddle.pos.y + 200 + BALL_RADIUS >= ball.pos.y) {
            if (abs(playerTwoPaddle.pos.x - BALL_RADIUS - ball.pos.x) < 5) {
                ball.angle = 180 - ball.angle;
                ball.angle = 180 + ball.angle;
            }
        }
    }

    void render(RenderContext& ctx) { 
        ctx.draw(playerOnePaddle.getDrawRect());
        ctx.draw(playerTwoPaddle.getDrawRect());
        ball.draw(ctx);
        board.draw(ctx);
        go.draw(ctx);
    }

    void finish() {

    }
};

int main() {  
    PongGame game;
    build(game);
}
