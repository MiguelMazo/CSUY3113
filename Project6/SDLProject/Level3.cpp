#include "Level3.h"
#define LEVEL3_WIDTH 20
#define LEVEL3_HEIGHT 8
#define LEVEL3_ENEMYCOUNT 2

bool finished = false;

unsigned int level3_data[] =
{
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 0, 0, 0, 1, 1, 1, 1,
 3, 1, 1, 1, 1, 0, 0, 0, 0, 1, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2,
 3, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2
};

void Level3::Initialize() {
    // Move over all of the player and enemy code from initialization.
    // Inside of Initialize

    state.nextScene = -1;

    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL3_WIDTH, LEVEL3_HEIGHT, level3_data, mapTextureID, 1.0f, 4, 1);
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
    state.player->entityType = PLAYER;
    state.player->enemiesToDefeat = LEVEL3_ENEMYCOUNT;
    state.player->lives = state.lives;

    state.enemies = new Entity[LEVEL3_ENEMYCOUNT];
    GLuint enemyTextureID = Util::LoadTexture("alien.png");

    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(7.0, -4, 0.0);
    state.enemies[0].jumpTimer = 2.5f;
    state.enemies[0].speed = 2.0f;
    state.enemies[0].aiType = BIRD;

    state.enemies[1].textureID = enemyTextureID;
    state.enemies[1].position = glm::vec3(10.0, -4, 0.0);
    state.enemies[1].jumpTimer = 2.5f;
    state.enemies[1].speed = 2.0f;
    state.enemies[1].aiType = BEAR;

    for (int i = 0; i < LEVEL3_ENEMYCOUNT; i++) {
        state.enemies[i].acceleration = glm::vec3(0.0, -9.0, 0.0);
        state.enemies[i].speed = 1.0f;
        state.enemies[i].entityType = ENEMY;
        state.enemies[i].Update(0, state.player, 0, NULL, state.map);
        state.enemies[i].width = 0.8;
        state.enemies[i].height = 0.8;
        state.enemies[i].aiState = IDLE;
    }
}
void Level3::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMYCOUNT, state.map);
    for (int i = 0; i < LEVEL3_ENEMYCOUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMYCOUNT, state.map);
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

    if (state.player->position.x >= 16 && state.player->position.y <= -3) {
        finished = true;
    }
}

int Level3::Render(ShaderProgram* program) {
    state.map->Render(program);
    state.player->Render(program);
    if (state.player->isActive == false) {
        return 1;
    }

    for (int i = 0; i < LEVEL3_ENEMYCOUNT; i++) {
        state.enemies[i].Render(program);
    }

    if (finished == true) {
        return 2;
    }
    return 0;
}