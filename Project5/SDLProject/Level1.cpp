#include "Level1.h"
#include <iostream>
using namespace std;

#define LEVEL1_WIDTH 20
#define LEVEL1_HEIGHT 8
#define LEVEL1_ENEMYCOUNT 1
unsigned int level1_data[] =
{
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
 3, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2,
 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2
};

void Level1::Initialize() {
	// Move over all of the player and enemy code from initialization.
    // Inside of Initialize

    state.nextScene = -1;

    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 4, 1);
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
    state.player->enemiesToDefeat = LEVEL1_ENEMYCOUNT;

    state.lives = 3;
    state.player->lives = state.lives;
    state.enemies = new Entity[LEVEL1_ENEMYCOUNT];
    GLuint enemyTextureID = Util::LoadTexture("alien.png");

    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(10.0, -4, 0.0);
    state.enemies[0].jumpTimer = 2.5f;
    state.enemies[0].speed = 2.0f;
    state.enemies[0].aiType = WALKER;


    for (int i = 0; i < LEVEL1_ENEMYCOUNT; i++) {
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
void Level1::Update(float deltaTime) {

    for (int i = 0; i < LEVEL1_ENEMYCOUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMYCOUNT, state.map);
        //state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMYCOUNT, state.map);
    }

    state.player->Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMYCOUNT, state.map);
    if (state.player->position.y < -8) {
        //cout << "IM HERE RN!\n" << state.player->position.y <<"\n";
        state.player->lives -= 1;
        state.player->lostLifeFlag = true;
        state.player->position = glm::vec3(5.0, 0.0, 0.0);
        if (state.player->lives == 0) {
            state.player->isActive = false;
        }
    }
    if (state.player->position.x >= 19 && state.player->position.y <= 11) {
        state.nextScene = 2;
        state.lives = state.player->lives;
    }
}
int Level1::Render(ShaderProgram* program) {
   
    
	state.map->Render(program);
	state.player->Render(program);

    //isactive means player is out of lives
    if (state.player->isActive == false) {
        return 1;
    }

    for (int i = 0; i < LEVEL1_ENEMYCOUNT; i++) {
        state.enemies[i].Render(program);
    }

    return 0;
}