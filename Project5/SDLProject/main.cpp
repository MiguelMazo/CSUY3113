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
#include "Scene.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "MainMenu.h"
#include <iostream>
#include <SDL_mixer.h>
using namespace std;

float timerCurrent = 0.0f;

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;

GLuint fontTextureID;
Mix_Music* music;
Mix_Chunk* loseLife;

Scene* currentScene;
Scene* sceneList[4];
int sceneNum = 0;

void SwitchToScene(Scene* scene) {
    currentScene = scene;
    currentScene->Initialize();
}


void Initialize() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    displayWindow = SDL_CreateWindow("Textured!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);

#ifdef _WINDOWS
    glewInit();
#endif

    glViewport(0, 0, 640, 480);

    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    music = Mix_LoadMUS("dooblydoo.mp3");
    Mix_PlayMusic(music, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);

    loseLife = Mix_LoadWAV("failure.wav");

    viewMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);

    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);

    glUseProgram(program.programID);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    fontTextureID = Util::LoadTexture("font1.png");

    sceneList[0] = new MainMenu();
    sceneList[1] = new Level1();
    sceneList[2] = new Level2();
    sceneList[3] = new Level3();
    SwitchToScene(sceneList[0]);
}

void ProcessInput() {

    currentScene->state.player->movement = glm::vec3(0);

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

            case SDLK_RETURN:
                if (currentScene->state.isMainMenu == true) {
                    SwitchToScene(sceneList[1]);
                 }
                break;

            case SDLK_SPACE:
                if (currentScene->state.player->collidedBottom) {
                    //state.player->airJumps = 1;
                    currentScene->state.player->jump = true;
                }

                else if (currentScene->state.player->airJumps > 0) {
                    currentScene->state.player->airJumps -= 1;
                    currentScene->state.player->jump = true;
                }
                // Some sort of action
                break;
            }
            break; // SDL_KEYDOWN
        }
    }

    const Uint8* keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_LEFT]) {
        currentScene->state.player->movement.x += -1.0f;
        currentScene->state.player->animIndices = currentScene->state.player->animLeft;
    }
    else if (keys[SDL_SCANCODE_RIGHT]) {
        currentScene->state.player->movement.x += 1.0f;
        currentScene->state.player->animIndices = currentScene->state.player->animRight;
    }

    if (glm::length(currentScene->state.player->movement) > 1.0f) {
        currentScene->state.player->movement = glm::normalize(currentScene->state.player->movement);
    }
}





float lastTicks = 0.0f;
#define FIXED_TIMESTEP 0.0166666f
float accumulator = 0.0f;


void Update() {
    //change this to do certain things dependant on the status
    float ticks = (float)SDL_GetTicks() / 1000.0f;  
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;

    deltaTime += accumulator;
    if (deltaTime < FIXED_TIMESTEP) {
        accumulator = deltaTime;
        return;
    }

    while (deltaTime >= FIXED_TIMESTEP) {
        currentScene->Update(FIXED_TIMESTEP);
        deltaTime -= FIXED_TIMESTEP;
    }

    accumulator = deltaTime;

    //cout << "IM HERE";
    // Inside Update

    if (currentScene->state.player->lostLifeFlag == true) {
        cout << currentScene->state.player->lostLifeFlag;
        Mix_PlayChannel(-1, loseLife, 0);
        currentScene->state.player->lostLifeFlag = false;
        Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
    }


    viewMatrix = glm::mat4(1.0f);
    if (currentScene->state.player->position.x > 5) {
       // cout << "FOLOWING\n";
        viewMatrix = glm::translate(viewMatrix, glm::vec3(-currentScene->state.player->position.x, 3.75, 0));
    }
    else {
       // cout << "FROZEN\n";
        viewMatrix = glm::translate(viewMatrix, glm::vec3(-5, 3.75, 0));
    }

    program.SetViewMatrix(viewMatrix);
}


void Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    int status = currentScene->Render(&program);

    if (status == -1) {
        Util::DrawText(&program, fontTextureID, "PRESS ENTER TO START", 0.4f, 0.01f, glm::vec3(1, -4, 0));
    }
    else if (status == 1) {
        Util::DrawText(&program, fontTextureID, "YOU LOSE", 0.4f, 0.01f, glm::vec3(4, -4, 0));
    }
    else if (status == 2) {
        Util::DrawText(&program, fontTextureID, "YOU WIN", 0.4f, 0.01f, glm::vec3(20, -4, 0));
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

        if (currentScene->state.nextScene >= 0) {
            Scene* nextScene = sceneList[currentScene->state.nextScene];
            nextScene->state.lives = currentScene->state.lives;
            SwitchToScene(sceneList[currentScene->state.nextScene]);
        }
        Render();
    }

    Shutdown();
    return 0;
}