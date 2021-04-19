#include "Entity.h"
#include <iostream>
using namespace std;

Entity::Entity()
{
    position = glm::vec3(0);
    movement = glm::vec3(0);
    acceleration = glm::vec3(0);
    velocity = glm::vec3(0);
    speed = 0;

    modelMatrix = glm::mat4(1.0f);
}

void Entity::setType(int id) {
    typeT = id;
}

bool Entity::CheckCollision(Entity* other) {
    if (isActive == false || other->isActive == false) {
        return false;
    }
    float xdist = fabs(position.x - other->position.x) - ((width + other->width) / 2.0f);
    float ydist = fabs(position.y - other->position.y) - ((height + other->height) / 2.0f);

    if (xdist < 0 && ydist < 0) return true;

    return false;
}

int Entity::CheckCollisionsY(Entity* objects, int objectCount)
{
    for (int i = 0; i < objectCount; i++)
    {
        Entity* object = &objects[i];

        if (CheckCollision(object))
        {
            float ydist = fabs(position.y - object->position.y);
            float penetrationY = fabs(ydist - (height / 2.0f) - (object->height / 2.0f));
            if (velocity.y > 0) {
                position.y -= penetrationY;
                velocity.y = 0;
                collidedTop = true;
            }
            else if (velocity.y < 0) {
                position.y += penetrationY;
                velocity.y = 0;
                collidedBottom = true;
            }

            return i;
        }
    }

    return -1;
}

int Entity::CheckCollisionsX(Entity* objects, int objectCount)
{
    for (int i = 0; i < objectCount; i++)
    {
        Entity* object = &objects[i];

        if (CheckCollision(object))
        {
            float xdist = fabs(position.x - object->position.x);
            float penetrationX =  fabs(xdist - (width / 2.0f) - (object->width / 2.0f));
            if (velocity.x > 0) {
                position.x -= penetrationX;
                velocity.x = 0;
                collidedRight = true;
            }
            else if (velocity.x < 0) {
                position.x += penetrationX;
                velocity.x = 0;
                collidedLeft = true;
            }

            return i;
        }
    }

    //No Collision
    return -1;
}

void Entity::AIRunaway(Entity* player) {
    switch (aiState) {
    case IDLE:
        if (glm::distance(position, player->position) < 3.0f) {
            aiState = WALKING;
        }
        break;
    case WALKING:
        if (position.x < -9.0 || position.x > 9.0) {
            movement = glm::vec3(0, 0, 0);
            break;
        }

        else if (player->position.x < position.x) {
            movement = glm::vec3(1, 0, 0);
        }
        else {
            movement = glm::vec3(-1, 0, 0);
        }
        break;
    case ATTACKING:
        break;
    }
}

void Entity::AIWaitAndGo(Entity* player) {
    switch (aiState) {
    case IDLE:
        if (glm::distance(position, player->position) < 3.0f) {
            aiState = WALKING;
        }
        break;
    case WALKING:
        if (player->position.x < position.x) {
            movement = glm::vec3(-1, 0, 0);
        }
        else {
            movement = glm::vec3(1, 0, 0);
        }
        break;
    case ATTACKING:
        break;
    }
}
void Entity::AIWalker(Entity *player) {
    switch (aiState) {
    case IDLE:
        aiState = WALKING;
        break;
    case WALKING:
        if (position.x < -8.5 || position.x > 8.5) {
            reverse *= -1;
        }
        
        movement = glm::vec3(1 * reverse, 0, 0);

        break;
    case ATTACKING:
        break;
    }
}

void Entity::AI(Entity *player) {
    switch (aiType) {
        case WALKER:
            AIWalker(player);
            break;
        case WAITANDGO:
            AIWaitAndGo(player);
            break;
    }

}

//int Entity::Update(float deltaTime, Entity* platforms, int platformCount, Entity* walls, int wallCount)//0 = game continue 1 = win 2 = lose
int Entity::Update(float deltaTime, Entity *player, Entity* enemies, int enemyCount, Map* map)//0 = game continue 1 = win 2 = lose
{
    if (isActive == false) return 0;
    
    collidedTop = false;
    collidedBottom = false;
    collidedRight = false;
    collidedLeft = false;

    if (entityType == ENEMY) {
        switch (aiType) {
        case WALKER:
            AIWalker(player);
            break;

        case WAITANDGO:
            AIWaitAndGo(player);
            break;

        case RUNAWAY:
            AIRunaway(player);
            break;
        }
    }

    if (animIndices != NULL) {
        if (glm::length(movement) != 0) {
            animTime += deltaTime;

            if (animTime >= 0.25f)
            {
                animTime = 0.0f;
                animIndex++;
                if (animIndex >= animFrames)
                {
                    animIndex = 0;
                }
            }
        }
        else { 
            animIndex = 0;
        }
    }

    if (jump) {
        jump = false;
        velocity.y += jumpPower;
    }

    velocity.x = movement.x * speed;
    velocity.y += acceleration.y * deltaTime;
    position += movement * speed * deltaTime;

    position.x += velocity.x * deltaTime; // Move on X



    
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5, 1.0f));
    modelMatrix = glm::translate(modelMatrix, position);


    //Goal 
    
    if (goalY > -1 || goalX > -1) {
        if (collidedBottom == true) {
            if (enemiesToDefeat == 1) {
                enemies[goalY].isActive = false;
                return 1;
            }

            else {
                enemiesToDefeat -= 1;
                enemies[goalY].isActive = false;
            }
        }

        else {
            isActive = false;
            return 2;
        }
    }
    

    //cout << collidedBottom << " , " << airJumps << "\n";
    //if (collidedBottom == true) {
    //    airJumps = 1;
    //}

    return 0;
}

void Entity::DrawSpriteFromTextureAtlas(ShaderProgram* program, GLuint textureID, int index)
{

    float u = (float)(index % animCols) / (float)animCols;
    float v = (float)(index / animCols) / (float)animRows;

    float width = 1.0f / (float)animCols;
    float height = 1.0f / (float)animRows;

    float texCoords[] = { u, v + height, u + width, v + height, u + width, v,
        u, v + height, u + width, v, u, v };

    float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };

    glBindTexture(GL_TEXTURE_2D, textureID);

    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);

    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}

void Entity::Render(ShaderProgram* program) {

    if (isActive == false) return;

    program->SetModelMatrix(modelMatrix);

    /*if (animIndices != NULL) {
        DrawSpriteFromTextureAtlas(program, textureID, animIndices[animIndex]);
        return;
    }*/

    float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };

    glBindTexture(GL_TEXTURE_2D, textureID);

    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);

    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}