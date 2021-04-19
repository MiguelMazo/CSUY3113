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
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "map.h"
#include "Entity.h"

int GOAL_COUNT = 3;
int WALL_COUNT = 88;
int ENEMY_COUNT = 3;

// Add to GameState (remove platforms)
// Add to top of file
#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 5
unsigned int level1_data[] =
{
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
1, 1, 1, 1, 0, 0, 1, 1, 1, 2, 2, 2, 2, 2,
2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2
};


float timerCurrent = 0.0f;
struct GameState {
    int status = 0;
    Map* map;
    Entity* player;
    Entity* goal;
    Entity* enemies; 
};

GameState state;

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;
GLuint fontTextureID;
void DrawText(ShaderProgram* program, GLuint fontTextureID, std::string text,
    float size, float spacing, glm::vec3 position)
{
    float width = 1.0f / 16.0f;
    float height = 1.0f / 16.0f;

    std::vector<float> vertices;
    std::vector<float> texCoords;

    for (int i = 0; i < text.size(); i++) {

        int index = (int)text[i];
        float offset = (size + spacing) * i;
        float u = (float)(index % 16) / 16.0f;
        float v = (float)(index / 16) / 16.0f;
        vertices.insert(vertices.end(), {
        offset + (-0.5f * size), 0.5f * size,
        offset + (-0.5f * size), -0.5f * size,
        offset + (0.5f * size), 0.5f * size,
        offset + (0.5f * size), -0.5f * size,
        offset + (0.5f * size), 0.5f * size,
        offset + (-0.5f * size), -0.5f * size,
            });
        texCoords.insert(texCoords.end(), {
        u, v,
        u, v + height,
        u + width, v,
        u + width, v + height,
        u + width, v,
        u, v + height,
            });

    } // end of for loop

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    program->SetModelMatrix(modelMatrix);

    glUseProgram(program->programID);

    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices.data());
    glEnableVertexAttribArray(program->positionAttribute);

    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords.data());
    glEnableVertexAttribArray(program->texCoordAttribute);

    glBindTexture(GL_TEXTURE_2D, fontTextureID);
    glDrawArrays(GL_TRIANGLES, 0, (int)(text.size() * 6));

    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);

}
GLuint LoadTexture(const char* filePath) {
    int w, h, n;
    unsigned char* image = stbi_load(filePath, &w, &h, &n, STBI_rgb_alpha);

    if (image == NULL) {
        std::cout << "Unable to load image. Make sure the path is correct\n";
        assert(false);
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(image);
    return textureID;
}


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


    // Initialize Game Objects

    // Initialize Player
    state.player = new Entity();
    state.player->setType(0);
    state.player->position = glm::vec3(0, -5.0, 0.0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, -11.0f, 0);
    state.player->speed = 5.0f;
    state.player->textureID = LoadTexture("spaceship.png");
    state.player->height = 1.0f;
    state.player->width = 1.0f;
    state.player->jumpPower = 10.0f;
    state.player->entityType = PLAYER;
    state.player->enemiesToDefeat = ENEMY_COUNT;

    state.enemies = new Entity[ENEMY_COUNT];
    GLuint enemyTextureID = LoadTexture("alien.png");

    fontTextureID = LoadTexture("font1.png");

    //state.goal = new Entity[GOAL_COUNT];
    //GLuint platformTextureID = LoadTexture("platformPack_tile001.png");
    /* Make the goal
    state.goal[0].textureID = platformTextureID;
    state.goal[0].position = glm::vec3(-1, -1.75, 0);

    state.goal[1].textureID = platformTextureID;
    state.goal[1].position = glm::vec3(0, -1.75, 0);

    state.goal[2].textureID = platformTextureID;
    state.goal[2].position = glm::vec3(1, -1.75, 0);

    for (int i = 0; i < GOAL_COUNT; i++) {
        state.goal[i].Update(0, NULL, 0, NULL, 0);
        state.goal[i].setType(1);
    }

    */
    //Make the walls
    
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
        state.enemies[i].Update(0, state.player, NULL, 0, state.map);
        state.enemies[i].width = 0.8;
        state.enemies[i].height = 0.8;
        state.enemies[i].aiState = IDLE;
        state.enemies[i].jumpPower = 10.0f;
        //state.goal[i].setType(2);
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
}


void Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    //for (int i = 0; i < GOAL_COUNT; i++) {
    //    state.goal[i].Render(&program);
    //}

    state.player->Render(&program);

    for (int i = 0; i < WALL_COUNT; i++) {
        state.walls[i].Render(&program);
    }

    for (int i = 0; i < ENEMY_COUNT; i++) {
        state.enemies[i].Render(&program);
    }


    if (state.status == 1) {
        DrawText(&program, fontTextureID, "MISSION SUCCESSFUL", 0.35f, 0.01f, glm::vec3(-3.0f, 0.0, 0));
    }

    else if (state.status == 2) {
        DrawText(&program, fontTextureID, "MISSION FAILED", 0.4f, 0.01f, glm::vec3(-2.5f, -0.5, 0));
        DrawText(&program, fontTextureID, "TRY AGAIN!", 0.3f, 0.01f, glm::vec3(-1.3f, -1.5, 0));
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