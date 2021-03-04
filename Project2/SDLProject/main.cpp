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


SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix, modelMatrix2, ballMatrix;


glm::vec3 player1_position = glm::vec3(4.5, 0, 0);
glm::vec3 player1_movement = glm::vec3(0, 0, 0);
float player1_speed = 5.0f;
float player1_width = 0.3f;
float player1_height = 1.5f;

glm::vec3 player2_position = glm::vec3(-4.5, 0, 0);
glm::vec3 player2_movement = glm::vec3(0, 0, 0);
float player2_speed = 5.0f;
float player2_width = 0.3f;
float player2_height = 1.5f;

glm::vec3 ball_position = glm::vec3(0, 0, 0);
glm::vec3 ball_movement = glm::vec3(1, 1, 0);
float ball_speed = 2.0f;
float ballX = 1.0f;
float ballY = 1.0f;
float ball_width = 0.2;
float ball_height = 0.2f;

GLuint playerTextureID1;
GLuint playerTextureID2;
GLuint ballTextureID;
GLuint fontTextureID;

int scoreP1 = 0;
int scoreP2 = 0;

bool start = false;

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
    displayWindow = SDL_CreateWindow("Triangle!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);

#ifdef _WINDOWS
    glewInit();
#endif

    glViewport(0, 0, 640, 480);

    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");

    viewMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);
    modelMatrix2 = glm::mat4(1.0f);
    ballMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);

    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    //program.SetColor(1.0f, 0.0f, 0.0f, 1.0f);

    glUseProgram(program.programID);

    glClearColor(0.5f, 0.5f, 1.0f, 1.0f);

    glEnable(GL_BLEND);
    // Good setting for transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    playerTextureID1 = LoadTexture("paddle.png");
    playerTextureID2 = LoadTexture("paddle.png");
    ballTextureID = LoadTexture("pokeball.png");
    fontTextureID = LoadTexture("font1.png");
}

void ProcessInput() {

    player1_movement = glm::vec3(0, 0, 0);
    player2_movement = glm::vec3(0, 0, 0);
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
        case SDL_WINDOWEVENT_CLOSE:
            gameIsRunning = false;
            break;

        }
    }

    const Uint8* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_KP_ENTER]) {
        start = true;
    }
    if (keys[SDL_SCANCODE_UP]) {
        if (player1_position.y < 3.5f) {
            player1_movement.y = 1.0f;
        }
    }
    else if (keys[SDL_SCANCODE_DOWN]) {
        if (player1_position.y > -3.5f) {
            player1_movement.y = -1.0f;
        }
    }

    if (keys[SDL_SCANCODE_W]) {
        if (player2_position.y < 3.5f) {
            player2_movement.y = 1.0f;
        }
    }
    else if (keys[SDL_SCANCODE_S]) {
        if (player2_position.y > -3.5f) {
            player2_movement.y = -1.0f;
        }
    }
}


float lastTicks = 0.0f;
void Update() { 
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;
    
    
    player1_position += player1_movement * player1_speed * deltaTime;

    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, player1_position);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(2.0, 2.0, 1.0));

    player2_position += player2_movement * player2_speed * deltaTime;

    modelMatrix2 = glm::mat4(1.0f); 
    modelMatrix2 = glm::translate(modelMatrix2, player2_position);
    modelMatrix2 = glm::scale(modelMatrix2, glm::vec3(-2.0, 2.0, 1.0));

    
    if (ball_position.y > 3.5f) {
        ballY *= -1.0f;
    }

    if (ball_position.y < -3.5f) {
        ballY *= -1.0f;
    }

    ball_movement = glm::vec3(ballX, ballY, 0);

    if (start == false) {
        ball_movement = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    ball_position += ball_movement * ball_speed * deltaTime;

    if (ball_position.x > 5) {
        ball_position.x = 0.0f;
        ball_position.y = 0.0f;
        scoreP2 += 1;
    }

    if (ball_position.x < -5) {
        ball_position.x = 0.0f;
        ball_position.y = 0.0f;
        scoreP1 += 1;
    }
    float xdiff, ydiff, xdistance, ydistance;
    xdiff = fabs(ball_position.x - player1_position.x);
    ydiff = fabs(ball_position.y - player1_position.y);
    xdistance = xdiff - (ball_width + player1_width) / 2;
    ydistance = ydiff - (ball_height + player1_height) / 2;

    if (ydistance == 0 && xdistance > 0) {
        ballY *= -1.0f;
    }

    else if (xdistance < 0 && ydistance < 0) {
        ballX *= -1.0f;
    }

    xdiff = fabs(ball_position.x - player2_position.x);
    ydiff = fabs(ball_position.y - player2_position.y);
    xdistance = xdiff - (ball_width + player2_width) / 2;
    ydistance = ydiff - (ball_height + player2_height) / 2;

    if (ydistance == 0 && xdistance > 0) {
        ballY *= -1.0f;
    }

    if (xdistance < 0 && ydistance < 0) {
        ballX *= -1.0f;
    }

    ball_movement.x = ballX;
    ball_movement.y = ballY;
    ballMatrix = glm::mat4(1.0f);
    ballMatrix = glm::translate(ballMatrix, ball_position);
    ballMatrix = glm::scale(ballMatrix, glm::vec3(0.5, 0.5, 1.0));
}

void Render() {
    glClear(GL_COLOR_BUFFER_BIT);
    program.SetModelMatrix(modelMatrix);
    float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program.positionAttribute);
    glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program.texCoordAttribute);
    glBindTexture(GL_TEXTURE_2D, playerTextureID1);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(program.positionAttribute);
    glDisableVertexAttribArray(program.texCoordAttribute);

    program.SetModelMatrix(modelMatrix2);
    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program.positionAttribute);
    glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program.texCoordAttribute);
    glBindTexture(GL_TEXTURE_2D, playerTextureID2);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(program.positionAttribute);
    glDisableVertexAttribArray(program.texCoordAttribute);

    program.SetModelMatrix(ballMatrix);
    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program.positionAttribute);
    glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program.texCoordAttribute);
    glBindTexture(GL_TEXTURE_2D, ballTextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(program.positionAttribute);
    glDisableVertexAttribArray(program.texCoordAttribute);

    DrawText(&program, fontTextureID, std::to_string(scoreP1), 0.5f, -0.25f, glm::vec3(1.75f, 0.0, 0));
    DrawText(&program, fontTextureID, std::to_string(scoreP2), 0.5f, -0.25f, glm::vec3(-1.75, 0.0, 0));


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
