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
int WALL_COUNT = 25;
struct GameState {
    int status = 0;
    Entity* player;
    Entity* goal;
    Entity* walls;
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
    state.player->position = glm::vec3(0, 4.0, 0.0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, -0.2f, 0);
    state.player->speed = 1.0f;
    state.player->textureID = LoadTexture("spaceship.png");
    state.player->height = 0.8f;
    state.player->width = 0.8f;

    state.goal = new Entity[GOAL_COUNT];
    state.walls = new Entity[WALL_COUNT];
    GLuint platformTextureID = LoadTexture("platformPack_tile001.png");
    GLuint wallsTextureID = LoadTexture("platformPack_tile007.png");
    fontTextureID = LoadTexture("font1.png");
    // Make the goal
    state.goal[0].textureID = platformTextureID;
    state.goal[0].position = glm::vec3(-1, -3.75, 0);

    state.goal[1].textureID = platformTextureID;
    state.goal[1].position = glm::vec3(0, -3.75, 0);

    state.goal[2].textureID = platformTextureID;
    state.goal[2].position = glm::vec3(1, -3.75, 0);

    for (int i = 0; i < GOAL_COUNT; i++) {
        state.goal[i].Update(0, NULL, 0, NULL, 0);
        state.goal[i].setType(1);
    }

    //Make the walls
    state.walls[0].textureID = wallsTextureID;
    state.walls[0].position = glm::vec3(4.5, -4, 0);

    state.walls[1].textureID = wallsTextureID;
    state.walls[1].position = glm::vec3(4.5, -3, 0);

    state.walls[2].textureID = wallsTextureID;
    state.walls[2].position = glm::vec3(4.5, -2, 0);

    state.walls[3].textureID = wallsTextureID;
    state.walls[3].position = glm::vec3(4.5, -1, 0);

    state.walls[4].textureID = wallsTextureID;
    state.walls[4].position = glm::vec3(4.5, 0, 0);

    state.walls[5].textureID = wallsTextureID;
    state.walls[5].position = glm::vec3(4.5, 1, 0);

    state.walls[6].textureID = wallsTextureID;
    state.walls[6].position = glm::vec3(4.5, 2, 0);

    state.walls[7].textureID = wallsTextureID;
    state.walls[7].position = glm::vec3(4.5, 3, 0);

    state.walls[8].textureID = wallsTextureID;
    state.walls[8].position = glm::vec3(4.5, 4, 0);

    state.walls[9].textureID = wallsTextureID;
    state.walls[9].position = glm::vec3(-4.5, -4, 0);

    state.walls[10].textureID = wallsTextureID;
    state.walls[10].position = glm::vec3(-4.5, -3, 0);

    state.walls[11].textureID = wallsTextureID;
    state.walls[11].position = glm::vec3(-4.5, -2, 0);

    state.walls[12].textureID = wallsTextureID;
    state.walls[12].position = glm::vec3(-4.5, -1, 0);

    state.walls[13].textureID = wallsTextureID;
    state.walls[13].position = glm::vec3(-4.5, 0, 0);

    state.walls[14].textureID = wallsTextureID;
    state.walls[14].position = glm::vec3(-4.5, 1, 0);

    state.walls[15].textureID = wallsTextureID;
    state.walls[15].position = glm::vec3(-4.5, 2, 0);

    state.walls[16].textureID = wallsTextureID;
    state.walls[16].position = glm::vec3(-4.5, 3, 0);

    state.walls[17].textureID = wallsTextureID;
    state.walls[17].position = glm::vec3(-4.5, 4, 0);

    state.walls[18].textureID = wallsTextureID;
    state.walls[18].position = glm::vec3(1, .75, 0);

    state.walls[19].textureID = wallsTextureID;
    state.walls[19].position = glm::vec3(-1, .75, 0);

    state.walls[20].textureID = wallsTextureID;
    state.walls[20].position = glm::vec3(0, .75, 0);

    state.walls[21].textureID = wallsTextureID;
    state.walls[21].position = glm::vec3(-2, -3.75, 0);

    state.walls[22].textureID = wallsTextureID;
    state.walls[22].position = glm::vec3(-3, -3.75, 0);

    state.walls[23].textureID = wallsTextureID;
    state.walls[23].position = glm::vec3(2, -3.75, 0);

    state.walls[24].textureID = wallsTextureID;
    state.walls[24].position = glm::vec3(3, -3.75, 0);
    
    for (int i = 0; i < WALL_COUNT; i++) {
        state.walls[i].Update(0, NULL, 0, NULL, 0);
        state.goal[i].setType(2);
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
                // Some sort of action
                break;
            }
            break; // SDL_KEYDOWN
        }
    }

    const Uint8* keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_LEFT]) {
        state.player->acceleration.x = -30.0f;
        state.player->animIndices = state.player->animLeft;
    }
    else if (keys[SDL_SCANCODE_RIGHT]) {
        state.player->acceleration.x = 30.0f;
        state.player->animIndices = state.player->animRight;
    }


}

float lastTicks = 0.0f;

#define FIXED_TIMESTEP 0.0166666f
float accumulator = 0.0f;

void Update() {
    if (state.status == 0) {
        float ticks = (float)SDL_GetTicks() / 1000.0f;
        float deltaTime = ticks - lastTicks;
        lastTicks = ticks;

        deltaTime += accumulator;
        if (deltaTime < FIXED_TIMESTEP) {
            accumulator = deltaTime;
            return;
        }

        while (deltaTime >= FIXED_TIMESTEP) {
            // Update. Notice it's FIXED_TIMESTEP. Not deltaTime
            state.status = state.player->Update(FIXED_TIMESTEP, state.goal, GOAL_COUNT, state.walls, WALL_COUNT);

            deltaTime -= FIXED_TIMESTEP;
        }

        accumulator = deltaTime;
    }
}


void Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < GOAL_COUNT; i++) {
        state.goal[i].Render(&program);
    }

    for (int i = 0; i < WALL_COUNT; i++) {
        state.walls[i].Render(&program);
    }

    state.player->Render(&program);

    if (state.status == 1) {
        DrawText(&program, fontTextureID, "MISSION SUCCESSFUL", 0.35f, 0.01f, glm::vec3(-3.0f, 0.0, 0));
    }

    else if (state.status == 2) {
        DrawText(&program, fontTextureID, "MISSION FAILED", 0.4f, 0.01f, glm::vec3(-2.5f, -0.5, 0));
        DrawText(&program, fontTextureID, "WE'LL GET EM NEXT TIME", 0.3f, 0.01f, glm::vec3(-3.0f, -1.5, 0));
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