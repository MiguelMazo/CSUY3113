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

#include "Entity.h"

int GOAL_COUNT = 3;
int WALL_COUNT = 88;
int ENEMY_COUNT = 3;

float timerCurrent = 0.0f;
struct GameState {
    int status = 0;
    Entity* player;
    Entity* goal;
    Entity* walls;
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

    state.walls = new Entity[WALL_COUNT];
    GLuint wallsTextureID = LoadTexture("platformPack_tile007.png");

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

    state.walls[0].textureID = wallsTextureID;
    state.walls[0].position = glm::vec3(10.0, -4, 0);

    state.walls[1].textureID = wallsTextureID;
    state.walls[1].position = glm::vec3(10.0, -3, 0);

    state.walls[2].textureID = wallsTextureID;
    state.walls[2].position = glm::vec3(10.0, -2, 0);

    state.walls[3].textureID = wallsTextureID;
    state.walls[3].position = glm::vec3(10.0, -1, 0);

    state.walls[4].textureID = wallsTextureID;
    state.walls[4].position = glm::vec3(10.0, 0, 0);

    state.walls[5].textureID = wallsTextureID;
    state.walls[5].position = glm::vec3(10.0, 1, 0);

    state.walls[6].textureID = wallsTextureID;
    state.walls[6].position = glm::vec3(10.0, 2, 0);

    state.walls[7].textureID = wallsTextureID;
    state.walls[7].position = glm::vec3(10.0, 3, 0);

    state.walls[8].textureID = wallsTextureID;
    state.walls[8].position = glm::vec3(10.0, 4, 0);

    state.walls[9].textureID = wallsTextureID;
    state.walls[9].position = glm::vec3(-10.0, -4, 0);

    state.walls[10].textureID = wallsTextureID;
    state.walls[10].position = glm::vec3(-10.0, -3, 0);

    state.walls[11].textureID = wallsTextureID;
    state.walls[11].position = glm::vec3(-10.0, -2, 0);

    state.walls[12].textureID = wallsTextureID;
    state.walls[12].position = glm::vec3(-10.0, -1, 0);

    state.walls[13].textureID = wallsTextureID;
    state.walls[13].position = glm::vec3(-10.0, 0, 0);

    state.walls[14].textureID = wallsTextureID;
    state.walls[14].position = glm::vec3(-10.0, 1, 0);

    state.walls[15].textureID = wallsTextureID;
    state.walls[15].position = glm::vec3(-10.0, 2, 0);

    state.walls[16].textureID = wallsTextureID;
    state.walls[16].position = glm::vec3(-10.0, 3, 0);

    state.walls[17].textureID = wallsTextureID;
    state.walls[17].position = glm::vec3(-10.0, 4, 0);

    state.walls[18].textureID = wallsTextureID;
    state.walls[18].position = glm::vec3(1, -7.0, 0);

    state.walls[19].textureID = wallsTextureID;
    state.walls[19].position = glm::vec3(-1, -7.0, 0);

    state.walls[20].textureID = wallsTextureID;
    state.walls[20].position = glm::vec3(0, -7.0, 0);

    state.walls[21].textureID = wallsTextureID;
    state.walls[21].position = glm::vec3(-2, -7.0, 0);

    state.walls[22].textureID = wallsTextureID;
    state.walls[22].position = glm::vec3(-3, -7.0, 0);

    state.walls[23].textureID = wallsTextureID;
    state.walls[23].position = glm::vec3(2, -7.0, 0);

    state.walls[24].textureID = wallsTextureID;
    state.walls[24].position = glm::vec3(3, -7.0, 0);

    state.walls[25].textureID = wallsTextureID;
    state.walls[25].position = glm::vec3(4, -7.0, 0);

    state.walls[26].textureID = wallsTextureID;
    state.walls[26].position = glm::vec3(-4, -7.0, 0);

    state.walls[27].textureID = wallsTextureID;
    state.walls[27].position = glm::vec3(5, -7.0, 0);

    state.walls[28].textureID = wallsTextureID;
    state.walls[28].position = glm::vec3(-5, -7.0, 0);

    state.walls[29].textureID = wallsTextureID;
    state.walls[29].position = glm::vec3(6, -7.0, 0);

    state.walls[30].textureID = wallsTextureID;
    state.walls[30].position = glm::vec3(-6, -7.0, 0);

    state.walls[31].textureID = wallsTextureID;
    state.walls[31].position = glm::vec3(7, -7.0, 0);

    state.walls[32].textureID = wallsTextureID;
    state.walls[32].position = glm::vec3(-7, -7.0, 0);

    state.walls[33].textureID = wallsTextureID;
    state.walls[33].position = glm::vec3(8, -7.0, 0);

    state.walls[34].textureID = wallsTextureID;
    state.walls[34].position = glm::vec3(-8, -7.0, 0);

    state.walls[35].textureID = wallsTextureID;
    state.walls[35].position = glm::vec3(9, -7.0, 0);

    state.walls[36].textureID = wallsTextureID;
    state.walls[36].position = glm::vec3(-9, -7.0, 0);

    state.walls[37].textureID = wallsTextureID;
    state.walls[37].position = glm::vec3(10, -7.0, 0);

    state.walls[38].textureID = wallsTextureID;
    state.walls[38].position = glm::vec3(-10, -7.0, 0);

    state.walls[39].textureID = wallsTextureID;
    state.walls[39].position = glm::vec3(10, -7.0, 0);

    state.walls[40].textureID = wallsTextureID;
    state.walls[40].position = glm::vec3(-10, -7.0, 0);

    state.walls[41].textureID = wallsTextureID;
    state.walls[41].position = glm::vec3(10, -6.0, 0);

    state.walls[42].textureID = wallsTextureID;
    state.walls[42].position = glm::vec3(-10, -6.0, 0);

    state.walls[43].textureID = wallsTextureID;
    state.walls[43].position = glm::vec3(10, -5.0, 0);

    state.walls[44].textureID = wallsTextureID;
    state.walls[44].position = glm::vec3(-10, -5.0, 0);

    state.walls[45].textureID = wallsTextureID;
    state.walls[45].position = glm::vec3(10.0, 5.0, 0);

    state.walls[46].textureID = wallsTextureID;
    state.walls[46].position = glm::vec3(-10.0, 5.0, 0);

    state.walls[47].textureID = wallsTextureID;
    state.walls[47].position = glm::vec3(10.0, 6.0, 0);

    state.walls[48].textureID = wallsTextureID;
    state.walls[48].position = glm::vec3(-10.0, 6.0, 0);

    state.walls[49].textureID = wallsTextureID;
    state.walls[49].position = glm::vec3(10.0, 7.0, 0);

    state.walls[50].textureID = wallsTextureID;
    state.walls[50].position = glm::vec3(-10.0, 7.0, 0);
    
    state.walls[51].textureID = wallsTextureID;
    state.walls[51].position = glm::vec3(1, 7.0, 0);

    state.walls[52].textureID = wallsTextureID;
    state.walls[52].position = glm::vec3(-1, 7.0, 0);

    state.walls[53].textureID = wallsTextureID;
    state.walls[53].position = glm::vec3(0, 7.0, 0);

    state.walls[54].textureID = wallsTextureID;
    state.walls[54].position = glm::vec3(-2, 7.0, 0);

    state.walls[55].textureID = wallsTextureID;
    state.walls[55].position = glm::vec3(-3, 7.0, 0);

    state.walls[56].textureID = wallsTextureID;
    state.walls[56].position = glm::vec3(2, 7.0, 0);

    state.walls[57].textureID = wallsTextureID;
    state.walls[57].position = glm::vec3(3, 7.0, 0);

    state.walls[58].textureID = wallsTextureID;
    state.walls[58].position = glm::vec3(4, 7.0, 0);

    state.walls[59].textureID = wallsTextureID;
    state.walls[59].position = glm::vec3(-4,7.0, 0);

    state.walls[60].textureID = wallsTextureID;
    state.walls[60].position = glm::vec3(5, 7.0, 0);

    state.walls[61].textureID = wallsTextureID;
    state.walls[61].position = glm::vec3(-5, 7.0, 0);

    state.walls[62].textureID = wallsTextureID;
    state.walls[62].position = glm::vec3(6, 7.0, 0);

    state.walls[63].textureID = wallsTextureID;
    state.walls[63].position = glm::vec3(-6, 7.0, 0);

    state.walls[64].textureID = wallsTextureID;
    state.walls[64].position = glm::vec3(7, 7.0, 0);

    state.walls[65].textureID = wallsTextureID;
    state.walls[65].position = glm::vec3(-7, 7.0, 0);

    state.walls[66].textureID = wallsTextureID;
    state.walls[66].position = glm::vec3(8, 7.0, 0);

    state.walls[67].textureID = wallsTextureID;
    state.walls[67].position = glm::vec3(-8, 7.0, 0);

    state.walls[68].textureID = wallsTextureID;
    state.walls[68].position = glm::vec3(9, 7.0, 0);

    state.walls[69].textureID = wallsTextureID;
    state.walls[69].position = glm::vec3(-9, 7.0, 0);

    state.walls[70].textureID = wallsTextureID;
    state.walls[70].position = glm::vec3(10, 7.0, 0);

    state.walls[71].textureID = wallsTextureID;
    state.walls[71].position = glm::vec3(-10, 7.0, 0);

    state.walls[72].textureID = wallsTextureID;
    state.walls[72].position = glm::vec3(10, 7.0, 0);

    state.walls[73].textureID = wallsTextureID;
    state.walls[73].position = glm::vec3(5, -3, 0);

    state.walls[74].textureID = wallsTextureID;
    state.walls[74].position = glm::vec3(4, -3, 0);

    state.walls[75].textureID = wallsTextureID;
    state.walls[75].position = glm::vec3(6, -3, 0);

    state.walls[76].textureID = wallsTextureID;
    state.walls[76].position = glm::vec3(-5, -3, 0);

    state.walls[77].textureID = wallsTextureID;
    state.walls[77].position = glm::vec3(-4, -3, 0);

    state.walls[78].textureID = wallsTextureID;
    state.walls[78].position = glm::vec3(-6, -3, 0);

    state.walls[79].textureID = wallsTextureID;
    state.walls[79].position = glm::vec3(-1, 0, 0);

    state.walls[80].textureID = wallsTextureID;
    state.walls[80].position = glm::vec3(0, 0, 0);

    state.walls[81].textureID = wallsTextureID;
    state.walls[81].position = glm::vec3(1, 0, 0);

    state.walls[82].textureID = wallsTextureID;
    state.walls[82].position = glm::vec3(5, 3, 0);

    state.walls[83].textureID = wallsTextureID;
    state.walls[83].position = glm::vec3(4, 3, 0);

    state.walls[84].textureID = wallsTextureID;
    state.walls[84].position = glm::vec3(6, 3, 0);

    state.walls[85].textureID = wallsTextureID;
    state.walls[85].position = glm::vec3(-5, 3, 0);

    state.walls[86].textureID = wallsTextureID;
    state.walls[86].position = glm::vec3(-4, 3, 0);

    state.walls[87].textureID = wallsTextureID;
    state.walls[87].position = glm::vec3(-6, 3, 0);
    for (int i = 0; i < WALL_COUNT; i++) {
        state.walls[i].entityType = PLATFORM;
        state.walls[i].Update(0, NULL, 0, state.player, NULL, 0);
        state.walls[i].width = 1.0;
        state.walls[i].height = 1.0;
        //state.goal[i].setType(2);
    }

    for (int i = 0; i < ENEMY_COUNT; i++) {
        state.enemies[i].acceleration = glm::vec3(0.0, -9.0, 0.0);
        state.enemies[i].speed = 1.0f;
        state.enemies[i].entityType = ENEMY;
        state.enemies[i].Update(0, NULL, 0, state.player, NULL, 0);
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
                state.status = state.player->Update(FIXED_TIMESTEP, state.walls, WALL_COUNT, state.player, state.enemies, ENEMY_COUNT);
            }

            for (int i = 0; i < ENEMY_COUNT; i++) {
                state.enemies[i].Update(FIXED_TIMESTEP, state.walls, WALL_COUNT, state.player, state.enemies, ENEMY_COUNT);
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