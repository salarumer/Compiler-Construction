#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 20
#define PLAYER_SYMBOL 'A'
#define ENEMY_SYMBOL 'V'
#define BULLET_SYMBOL '^'

typedef struct {
    int x, y;
} Entity;

typedef struct {
    Entity player;
    Entity enemies[5];
    Entity bullet;
    int score;
    bool gameOver;
} Game;

void init(Game *game) {
    // Initialize player
    game->player.x = SCREEN_WIDTH / 2;
    game->player.y = SCREEN_HEIGHT - 2;

    // Initialize enemies
    for (int i = 0; i < 5; ++i) {
        game->enemies[i].x = rand() % SCREEN_WIDTH;
        game->enemies[i].y = 1;
    }

    // Initialize bullet
    game->bullet.x = -1;
    game->bullet.y = -1;

    game->score = 0;
    game->gameOver = false;
}

void draw(const Game *game) {
    system("clear");

    // Draw player
    printf("\033[%d;%dH%c", game->player.y, game->player.x, PLAYER_SYMBOL);

    // Draw enemies
    for (int i = 0; i < 5; ++i) {
        printf("\033[%d;%dH%c", game->enemies[i].y, game->enemies[i].x, ENEMY_SYMBOL);
    }

    // Draw bullet
    if (game->bullet.y != -1) {
        printf("\033[%d;%dH%c", game->bullet.y, game->bullet.x, BULLET_SYMBOL);
    }

    // Print score
    printf("\033[%d;0HScore: %d", SCREEN_HEIGHT + 1, game->score);
}

void update(Game *game) {
    // Move bullet
    if (game->bullet.y != -1) {
        game->bullet.y--;
        // Check bullet collision with enemies
        for (int i = 0; i < 5; ++i) {
            if (game->bullet.y == game->enemies[i].y && game->bullet.x == game->enemies[i].x) {
                game->score++;
                game->bullet.y = -1;
                game->enemies[i].y = -1;
                game->enemies[i].x = -1;
            }
        }
    }

    // Move enemies
    for (int i = 0; i < 5; ++i) {
        if (game->enemies[i].y != -1) {
            game->enemies[i].y++;
            // Check enemy collision with player
            if (game->enemies[i].y == game->player.y && game->enemies[i].x == game->player.x) {
                game->gameOver = true;
                return;
            }
            // Check enemy reaching the bottom
            if (game->enemies[i].y >= SCREEN_HEIGHT) {
                game->gameOver = true;
                return;
            }
        }
    }
}

void handleInput(Game *game) {
    // Move player
    char input;
    scanf(" %c", &input);
    switch (input) {
        case 'a':
            if (game->player.x > 0)
                game->player.x--;
            break;
        case 'd':
            if (game->player.x < SCREEN_WIDTH - 1)
                game->player.x++;
            break;
        case ' ':
            // Shoot bullet
            if (game->bullet.y == -1) {
                game->bullet.x = game->player.x;
                game->bullet.y = game->player.y - 1;
            }
            break;
        default:
            break;
    }
}

int main() {
    srand(time(NULL));

    Game game;
    init(&game);

    while (!game.gameOver) {
        draw(&game);
        handleInput(&game);
        update(&game);
        usleep(100000); // sleep for 100 milliseconds
    }

    printf("\033[%d;0HGame Over! Your score: %d\n", SCREEN_HEIGHT + 2, game.score);

    return 0;
}