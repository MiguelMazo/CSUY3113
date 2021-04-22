#pragma once
#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Map.h"
enum EntityType {PLAYER, PLATFORM, ENEMY};
enum AIType {WALKER, WAITANDGO, RUNAWAY};
enum AIState { IDLE, WALKING, ATTACKING };

class Entity {
public:
    EntityType entityType;
    AIType aiType;
    AIState aiState; 
    glm::vec3 position;
    glm::vec3 movement;
    glm::vec3 acceleration;
    glm::vec3 velocity;
    float speed;
    float width = 0.8;
    float height = 0.8;
    float jumpTimer = 0.0;
    float timerCurrent = 0.0f;
    int typeT = 2; //0 = Player, 1 = Goal, 2 = Wall, 3 = Enemy
    bool isActive = true;
    bool collidedTop = false;
    bool collidedBottom = false;
    bool collidedLeft = false;
    bool collidedRight = false;
    GLuint textureID;
    int goalX, goalY, wallX, wallY;
    glm::mat4 modelMatrix;
    bool jump = false;
    float jumpPower = 0;
    int airJumps = 0;
    int reverse = -1;
    int enemiesToDefeat; 
    int lives = 3;
    bool lostLifeFlag = false;
    int* animRight = NULL;
    int* animLeft = NULL;
    int* animUp = NULL;
    int* animDown = NULL;
    int* animIndices = NULL;
    int animFrames = 0;
    int animIndex = 0;
    float animTime = 0;
    int animCols = 0;
    int animRows = 0;

    Entity();

    void setType(int id);
    bool CheckCollision(Entity* other);
    int Update(float deltaTime, Entity *player, Entity* objects, int objectCount, Map* map);
    void Render(ShaderProgram* program);
    void DrawSpriteFromTextureAtlas(ShaderProgram* program, GLuint textureID, int index);
    int CheckCollisionsY(Entity* objects, int objectCount);
    int CheckCollisionsX(Entity* objects, int objectCount);
    void CheckCollisionsX(Map* map);
    void CheckCollisionsY(Map* map);
    void AI(Entity *player);
    void AIWalker(Entity *player);
    void AIWaitAndGo(Entity* player);
    void AIRunaway(Entity* player);
    void loseLife(Entity* player);
};