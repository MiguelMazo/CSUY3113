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
#include <vector>
#include "map.h"
#include "Entity.h"
#include "util.h"

#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 8
unsigned int level1_data[] =
{
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
 3, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2,
 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

int ENEMY_COUNT = 3;
float timerCurrent = 0.0f;

struct GameState {
    Map* map;
    int status = 0;
    Entity* player;
    Entity* enemies; 
};

GameState state;

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;
GLuint fontTextureID;

void Initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Textured!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);

#ifdef _WINDOWS
    glewInit();
#endif

    glViewport(0, 0, 640, 480);

    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");

    viewMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);

    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);

    glUseProgram(program.programID);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Inside of Initialize
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
    state.player->enemiesToDefeat = ENEMY_COUNT;

    state.enemies = new Entity[ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("alien.png");

    fontTextureID = Util::LoadTexture("font1.png");
    
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(0.0, 1.0, 0.0);
    state.enemies[0].jumpTimer = 1.0f;
    state.enemies[0].speed = 1.0f;
    state.enemies[0].aiType = WAITANDGO;

    state.enemies[1].textureID = enemyTextureID;
    state.enemies[1].position = glm::vec3(1.0, 1.0, 0.0);
    state.enemies[1].jumpTimer = 2.5f;
    state.enemies[1].speed = 2.0f;
    state.enemies[1].aiType = WALKER;

    state.enemies[2].textureID = enemyTextureID;
    state.enemies[2].position = glm::vec3(-1.0, 1.0, 0.0);
    state.enemies[2].jumpTimer = 5.0f;
    state.enemies[2].speed = 3.0f;
    state.enemies[2].aiType = RUNAWAY;


    for (int i = 0; i < ENEMY_COUNT; i++) {
        state.enemies[i].acceleration = glm::vec3(0.0, -9.0, 0.0);
        state.enemies[i].speed = 1.0f;
        state.enemies[i].entityType = ENEMY;
        state.enemies[i].Update(0, state.player, 0, NULL, state.map);
        state.enemies[i].width = 0.8;
        state.enemies[i].height = 0.8;
        state.enemies[i].aiState = IDLE;
        state.enemies[i].jumpPower = 10.0f;
    }
}

void ProcessInput() {

    state.player->movement = glm::vec3(0);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
        case SDL_WINDOWEVENT_CLOSE:
            gameIsRunning = false;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                // Move the player left
                break;

            case SDLK_RIGHT:
                // Move the player right
                break;

            case SDLK_SPACE:
                if (state.player->collidedBottom) {
                    //state.player->airJumps = 1;
                    state.player->jump = true;
                }

                else if (state.player->airJumps > 0) {
                    state.player->airJumps -= 1;
                    state.player->jump = true;
                }
                // Some sort of action
                break;
            }
            break; // SDL_KEYDOWN
        }
    }

    const Uint8* keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_LEFT]) {
        state.player->movement.x += -1.0f;
        state.player->animIndices = state.player->animLeft;
    }
    else if (keys[SDL_SCANCODE_RIGHT]) {
        state.player->movement.x += 1.0f;
        state.player->animIndices = state.player->animRight;
    }

    if (glm::length(state.player->movement) > 1.0f) {
        state.player->movement = glm::normalize(state.player->movement);
    }
}

float lastTicks = 0.0f;

#define FIXED_TIMESTEP 0.0166666f
float accumulator = 0.0f;

void Update() {
    //change this to do certain things dependant on the status
    if (true) {
        float ticks = (float)SDL_GetTicks() / 1000.0f;  
        float deltaTime = ticks - lastTicks;
        lastTicks = ticks;

        for (int i = 0; i < ENEMY_COUNT; i++) {
            state.enemies[i].timerCurrent += deltaTime;
            if (state.enemies[i].timerCurrent >= state.enemies[i].jumpTimer && state.enemies[i].collidedBottom == true) {
                state.enemies[i].jump = true;
                state.enemies[i].timerCurrent -= state.enemies[i].jumpTimer;
            }

        }
        deltaTime += accumulator;
        if (deltaTime < FIXED_TIMESTEP) {
            accumulator = deltaTime;
            return;
        }

        while (deltaTime >= FIXED_TIMESTEP) {
            // Update. Notice it's FIXED_TIMESTEP. Not deltaTime
            if (state.status == 0) {
                state.status = state.player->Update(FIXED_TIMESTEP, state.player, state.enemies, ENEMY_COUNT, state.map);
            }

            for (int i = 0; i < ENEMY_COUNT; i++) {
                state.enemies[i].Update(FIXED_TIMESTEP, state.player, state.enemies, ENEMY_COUNT, state.map);
            }
            deltaTime -= FIXED_TIMESTEP;
        }

        accumulator = deltaTime;
    }

    // Inside Update
    viewMatrix = glm::mat4(1.0f);
    if (state.player->position.x > 5) {
        viewMatrix = glm::translate(viewMatrix, glm::vec3(-state.player->position.x, 3.75, 0));
    }
    else {
        viewMatrix = glm::translate(viewMatrix, glm::vec3(-5, 3.75, 0));
    }
}


void Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    program.SetViewMatrix(viewMatrix);
    state.map->Render(&program);
    state.player->Render(&program);

    for (int i = 0; i < ENEMY_COUNT; i++) {
        state.enemies[i].Render(&program);
    }


    if (state.status == 1) {
        Util::DrawText(&program, fontTextureID, "MISSION SUCCESSFUL", 0.35f, 0.01f, glm::vec3(-3.0f, 0.0, 0));
    }

    else if (state.status == 2) {
        Util::DrawText(&program, fontTextureID, "MISSION FAILED", 0.4f, 0.01f, glm::vec3(-2.5f, -0.5, 0));
        Util::DrawText(&program, fontTextureID, "TRY AGAIN!", 0.3f, 0.01f, glm::vec3(-1.3f, -1.5, 0));
    }

    SDL_GL_SwapWindow(displayWindow);
}


void Shutdown() {
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    Initialize();

    while (gameIsRunning) {
        ProcessInput();
        Update();
        Render();
    }

    Shutdown();
    return 0;
}