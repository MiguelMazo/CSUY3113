#include "Level2.h"
#define LEVEL2_WIDTH 14
#define LEVEL2_HEIGHT 8
#define LEVEL2_ENEMYCOUNT 1
unsigned int level2_data[] =
{
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 3,
 3, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 3, 3,
 3, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 3
};

void Level2::Initialize() {

    state.nextScene = -1;

    // Move over all of the player and enemy code from initialization.
    // Inside of Initialize
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL2_WIDTH, LEVEL2_HEIGHT, level2_data, mapTextureID, 1.0f, 4, 1);
    // Initialize Game Objects

    // Initialize Player
    state.player = new Entity();
    state.player->setType(0);
    state.player->position = glm::vec3(5.0, 0.0, 0.0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, -11.0f, 0);
    state.player->speed = 5.0f;
    state.player->textureID = Util::LoadTexture("spaceship.png");
    state.player->height = 1.0f;
    state.player->width = 1.0f;
    state.player->jumpPower = 7.5f;
    state.player->entityType = PLAYER;
    state.player->enemiesToDefeat = LEVEL2_ENEMYCOUNT;

    state.player->lives = state.lives;

    state.enemies = new Entity[LEVEL2_ENEMYCOUNT];
    GLuint enemyTextureID = Util::LoadTexture("alien.png");

    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(7, -2, 0.0);
    state.enemies[0].jumpTimer = 2.5f;
    state.enemies[0].speed = 2.0f;
    state.enemies[0].aiType = WAITANDGO;


    for (int i = 0; i < LEVEL2_ENEMYCOUNT; i++) {
        state.enemies[i].acceleration = glm::vec3(0.0, -9.0, 0.0);
        state.enemies[i].speed = 1.0f;
        state.enemies[i].entityType = ENEMY;
        state.enemies[i].Update(0, state.player, NULL, 0, state.map);
        state.enemies[i].width = 0.8;
        state.enemies[i].height = 0.8;
        state.enemies[i].aiState = IDLE;
        state.enemies[i].jumpPower = 10.0f;
    }
}
void Level2::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMYCOUNT, state.map);
    for (int i = 0; i < LEVEL2_ENEMYCOUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMYCOUNT, state.map);
        //state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMYCOUNT, state.map);
    }

    if (state.player->position.y < -8) {
        //cout << "IM HERE RN!\n" << state.player->position.y <<"\n";
        state.player->lives -= 1;
        state.player->lostLifeFlag = true;
        state.player->position = glm::vec3(5.0, 0.0, 0.0);
        if (state.player->lives == 0) {
            state.player->isActive = false;
        }
    }

    if (state.player->position.x >= 13 && state.player->position.y <= 5) {
        state.nextScene = 3;
        state.lives = state.player->lives;
    }
}

int Level2::Render(ShaderProgram* program) {
    state.map->Render(program);
    state.player->Render(program);

    if (state.player->isActive == false) {
        return 1;
    }

    for (int i = 0; i < LEVEL2_ENEMYCOUNT; i++) {
        state.enemies[i].Render(program);
    }

    return 0;
}