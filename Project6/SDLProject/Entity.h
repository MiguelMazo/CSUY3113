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
#include "Util.h"
#include "stdlib.h"
enum EntityType {PLAYER, PLATFORM, ENEMY, PROJECTILE};
enum AIType {BIRD, BEAR, SNAKE };
enum AIState { IDLE, WALKING, ATTACKING };
enum PType {BLUE, GREEN, RED };
enum Direction {UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT};
class Entity {
public:
    EntityType entityType;
    AIType aiType;
    AIState aiState; 
    Direction direction;
    PType projectileType;
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
    float shootTime = 0;
    int animCols = 4;
    int animRows = 4;
    int currentProjectiles = 0;
    int bounces = 0;
    bool isProj = false;
    bool iveShot = false;
    Entity* projectiles = NULL;
    int whoIsShooting = -1;
    bool shoot = false;

    Entity();

    void setType(int id);
    bool CheckCollision(Entity* other);
    int Update(float deltaTime, Entity *player, Entity* objects, int objectCount, Map* map);
    void Render(ShaderProgram* program);
    void DrawSpriteFromTextureAtlas(ShaderProgram* program, GLuint textureID, int index);
    int CheckCollisionsY(Entity* objects, int objectCount, Entity* player);
    int CheckCollisionsX(Entity* objects, int objectCount, Entity* player);
    void CheckCollisionsX(Map* map);
    void CheckCollisionsY(Map* map);
    void AI(Entity *player);
    void AIBird(Entity *player);
    void AIBear(Entity* player);
    void AISnake(Entity* player);
    void loseLife(Entity* player);
    void shootProjectile(PType type, int whoIsShooting);
};