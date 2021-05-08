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
    if (other == this) {
        return false;
    }
    if (isActive == false || other->isActive == false) {
        return false;
    }
    float xdist = fabs(position.x - other->position.x) - ((width + other->width) / 2.0f);
    float ydist = fabs(position.y - other->position.y) - ((height + other->height) / 2.0f);

    if (xdist < 0 && ydist < 0) return true;

    return false;
}


int Entity::CheckCollisionsY(Entity* objects, int objectCount, Entity* player)
{
    if (entityType == PROJECTILE) {
        if (CheckCollision(player))
        {
            float ydist = fabs(position.y - player->position.y);
            float penetrationY = fabs(ydist - (height / 2.0f) - (player->height / 2.0f));
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
            isActive = false;
            loseLife(player);
            return 1;
        }
    }
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

                if (entityType == PLAYER and object->entityType == ENEMY) {
                    loseLife(this);
                }

                if (object->entityType == ENEMY and entityType == PROJECTILE) {
                    player->projectileType = object->projectileType;
                    object->isActive = false;
                }
            }
            else if (velocity.y < 0) {
                position.y += penetrationY;
                velocity.y = 0;
                collidedBottom = true;

                if (object->entityType == ENEMY and entityType == PROJECTILE) {
                    object->isActive = false;
                    player->projectileType = object->projectileType;
                }

                if (entityType == PLAYER and object->entityType == ENEMY) {
                    loseLife(this);
                }
            }

            return 2;
        }
    }

    return 0;
}


void Entity::CheckCollisionsY(Map* map)
{
    // Probes for tiles
    glm::vec3 top = glm::vec3(position.x, position.y + (height / 2), position.z);
    glm::vec3 top_left = glm::vec3(position.x - (width / 2), position.y + (height / 2), position.z);
    glm::vec3 top_right = glm::vec3(position.x + (width / 2), position.y + (height / 2), position.z);

    glm::vec3 bottom = glm::vec3(position.x, position.y - (height / 2), position.z);
    glm::vec3 bottom_left = glm::vec3(position.x - (width / 2), position.y - (height / 2), position.z);
    glm::vec3 bottom_right = glm::vec3(position.x + (width / 2), position.y - (height / 2), position.z);

    float penetration_x = 0;
    float penetration_y = 0;

    if (map->IsSolid(top, &penetration_x, &penetration_y, isProj) && velocity.y > 0) {
        position.y -= penetration_y;
        velocity.y = 0;
        collidedTop = true;
    }
    else if (map->IsSolid(top_left, &penetration_x, &penetration_y, isProj) && velocity.y > 0) {
        position.y -= penetration_y;
        velocity.y = 0;
        collidedTop = true;
    }
    else if (map->IsSolid(top_right, &penetration_x, &penetration_y, isProj) && velocity.y > 0) {
        position.y -= penetration_y;
        velocity.y = 0;
        collidedTop = true;
    }
    if (map->IsSolid(bottom, &penetration_x, &penetration_y, isProj) && velocity.y < 0) {
        position.y += penetration_y;
        velocity.y = 0;
        collidedBottom = true;
    }
    else if (map->IsSolid(bottom_left, &penetration_x, &penetration_y, isProj) && velocity.y < 0) {
        position.y += penetration_y;
        velocity.y = 0;
        collidedBottom = true;
    }
    else if (map->IsSolid(bottom_right, &penetration_x, &penetration_y, isProj) && velocity.y < 0) {
        position.y += penetration_y;
        velocity.y = 0;
        collidedBottom = true;
    }
}

int Entity::CheckCollisionsX(Entity* objects, int objectCount, Entity* player)
{
    if (entityType == PROJECTILE){

        if (CheckCollision(player))
        {
            float xdist = fabs(position.x - player->position.x);
            float penetrationX = fabs(xdist - (width / 2.0f) - (player->width / 2.0f));


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

            isActive = false;
            loseLife(player);
            return 1;
        }
    }

    for (int i = 0; i < objectCount; i++)
    {
        Entity* object = &objects[i];

        if (CheckCollision(object))
        {
            float xdist = fabs(position.x - object->position.x);
            float penetrationX = fabs(xdist - (width / 2.0f) - (object->width / 2.0f));


            if (velocity.x > 0) {
                position.x -= penetrationX;
                velocity.x = 0;
                collidedRight = true;

                if (entityType == PLAYER and object->entityType == ENEMY) {
                    loseLife(this);
                }

                if (object->entityType == ENEMY and entityType == PROJECTILE) {
                    object->isActive = false;
                    player->projectileType = object->projectileType;
                }

            }
            else if (velocity.x < 0) {
                position.x += penetrationX;
                velocity.x = 0;
                collidedLeft = true;
 
                if (entityType == PLAYER and object->entityType == ENEMY) {
                    loseLife(this);
                }

                if (object->entityType == ENEMY and entityType == PROJECTILE) {
                    object->isActive = false;
                    player->projectileType = object->projectileType;
                }
            }
            return 1;
        }
    }

    return 0;
}


void Entity::CheckCollisionsX(Map* map)
{
    // Probes for tiles
    glm::vec3 left = glm::vec3(position.x - (width / 2), position.y, position.z);
    glm::vec3 right = glm::vec3(position.x + (width / 2), position.y, position.z);

    float penetration_x = 0;
    float penetration_y = 0;

    if (map->IsSolid(left, &penetration_x, &penetration_y, isProj) && velocity.x < 0) {
        position.x += penetration_x;
        velocity.x = 0;
        collidedLeft = true;
    }

    if (map->IsSolid(right, &penetration_x, &penetration_y, isProj) && velocity.x > 0) {
        position.x -= penetration_x;
        velocity.x = 0;
        collidedRight = true;
    }
}


void Entity::AISnake(Entity* player) {
    float x = player->position.x - position.x;
    float y = player->position.y - position.y;
    speed = 1.5;
    switch (aiState) {
    case IDLE:
        if (glm::distance(position, player->position) < 10.0f) {
            aiState = WALKING;
        }
        break;

    case WALKING:
        if (shoot == true) {
            aiState = ATTACKING;
        }
        if (x < -5) {
            movement = glm::vec3(-1, 0, 0);
            direction = LEFT;
        }
        else if (x > 5) {
            movement = glm::vec3(1, 0, 0);
            direction = RIGHT;
        }

        else {
            if (y < -1) {
                movement = glm::vec3(0, -1, 0);
                if (direction = RIGHT) {
                    direction = DOWNRIGHT;
                }

                else if (direction = LEFT) {
                    direction = DOWNLEFT;
                }

                else {
                    direction = DOWN;
                }
            }
            else if (y > 1) {

                movement = glm::vec3(0, 1, 0);
                if (direction = RIGHT) {
                    direction = UPRIGHT;
                }

                else if (direction = LEFT) {
                    direction = UPLEFT;
                }

                else {
                    direction = UP;
                }
            }

            else {
                direction = RIGHT;
            }
        }
        break;

    case ATTACKING:
        shoot = false;
        shootTime = 0.0f;
        shootProjectile(RED, -1);
        aiState = WALKING;
        break;
    }
}

void Entity::AIBear(Entity* player) {
    float x = player->position.x - position.x;
    float y = player->position.y - position.y;
    switch (aiState) {
    case IDLE:
        if (glm::distance(position, player->position) < 10.0f) {
            aiState = WALKING;
        }
        break;

    case WALKING:
        if (shoot == true) {
            aiState = ATTACKING;
        }
        if (x < -5) {
            movement = glm::vec3(-1, 0, 0);
            direction = LEFT;
        }
        else if (x > 5){
            movement = glm::vec3(1, 0, 0);
            direction = RIGHT;
        }

        else {
            if (y < -1) {
                movement = glm::vec3(0, -1, 0);
                if (direction = RIGHT) {
                    direction = DOWNRIGHT;
                }

                else if (direction = LEFT) {
                    direction = DOWNLEFT;
                }

                else {
                    direction = DOWN;
                }
            }
            else if (y > 1) {
                movement = glm::vec3(0, 1, 0);
                if (direction = RIGHT) {
                    direction = UPRIGHT;
                }

                else if (direction = LEFT) {
                    direction = UPLEFT;
                }

                else {
                    direction = UP;
                }
            }

            else {
                direction = RIGHT;
            }
        }
        break;

    case ATTACKING:
        shoot = false;
        shootTime = 0.0f;
        shootProjectile(GREEN, -1);
        aiState = WALKING;
        break;
    }
}
void Entity::AIBird(Entity *player) {
    float y = player->position.y - position.y;
    switch (aiState) {
    case IDLE:
        if (glm::distance(position, player->position) < 10.0f) {
            aiState = WALKING;
        }
        break;
    case WALKING:
        if (shoot == true) {
            aiState = ATTACKING;
        }
        if (-0.5 < y < -0.5) {
            direction = RIGHT;
        }
        
        else if (y < -0.5) {
            direction = DOWNRIGHT;
        }

        else if (y > 0.5) {
            direction = UPRIGHT;
        }
        break;

    case ATTACKING:
        shoot = false;
        shootTime = 0.0f;
        shootProjectile(BLUE, -1);
        aiState = WALKING;
        break;
    }
}

void Entity::AI(Entity *player) {
    switch (aiType) {
        case BIRD:
            AIBird(player);
            break;
        case BEAR:
            AIBear(player);
            break;
        case SNAKE:
            AISnake(player);
            break;
    }

}

//int Entity::Update(float deltaTime, Entity* platforms, int platformCount, Entity* walls, int wallCount)//0 = game continue 1 = win 2 = lose
int Entity::Update(float deltaTime, Entity *player, Entity* objects, int objectCount, Map* map)//0 = game continue 1 = win 2 = lose
{
    if (entityType == PROJECTILE) {
        if ((abs(position.x - player->position.x )> 10) or (abs(position.y - player->position.y) > 10)) {
            isActive == false;
        }
    }

    if (isActive == false) return 0;
    
    if (shoot == false) {
        shootTime += deltaTime;
    }

    if (shootTime >= 3.0f) {
        shoot = true;
    }

    collidedTop = false;
    collidedBottom = false;
    collidedRight = false;
    collidedLeft = false;

    if (entityType == ENEMY) {
        switch (aiType) {
        case BIRD:
            AIBird(player);
            break;

        case BEAR:
            AIBear(player);
            break;

        case SNAKE:
            AISnake(player);
            break;
        }
    }

    if (animIndices != NULL) {
        if (glm::length(movement) != 0 or aiType == BIRD) {
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

    velocity.x = movement.x * speed;
    velocity.y = movement.y * speed;
    velocity += acceleration * deltaTime;
    //position += movement * speed * deltaTime;

    //goalX = CheckCollisionsXGoal(platforms, platformCount);// Fix if needed

    position.y += velocity.y * deltaTime; // Move on Y
    CheckCollisionsY(map);
    CheckCollisionsY(objects, objectCount, player); // Fix if needed


    position.x += velocity.x * deltaTime; // Move on X
    CheckCollisionsX(map);
    CheckCollisionsX(objects, objectCount, player); // Fix if needed

    
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    if (entityType == PROJECTILE) {
        if (collidedBottom or collidedTop) {
            if (bounces > 0) {
                movement.y *= -1;
                bounces -= 1;
            }
            else {
                isActive = false;
            }
        }

        if (collidedLeft or collidedRight) {
            if (bounces > 0) {
                movement.x *= -1;
                bounces -= 1;
            }
            else {
                isActive = false;
            }
        }
        if (projectileType == BLUE) {
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5, 0.5, 0.0));
        }

        if (projectileType == GREEN) {
            modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0, 1.0, 0.0));
        }
        if (projectileType == RED) {
            modelMatrix = glm::scale(modelMatrix, glm::vec3(1.5, 1.5, 0.0));
        }
    }

    return 0;
}

void Entity::loseLife(Entity* player) {
    player->lives -= 1;
    player->lostLifeFlag = true;
    player->position.x = player->position.x - 0.5f;
    if (player->lives == 0) {
        player->isActive = false;
    }
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

    if (animIndices != NULL) {
        DrawSpriteFromTextureAtlas(program, textureID, animIndices[animIndex]);
        return;
    }

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

void Entity::shootProjectile(PType type, int whoIsShooting) {
    projectiles = new Entity();
    projectiles->projectileType = type;
    projectiles->position = glm::vec3(position.x + 0.7 * whoIsShooting, position.y, 0.0);
    if (direction == UP) {
        projectiles->position = glm::vec3(position.x, position.y + 1.0, 0.0);
        projectiles->movement = glm::vec3(0.0, 3.0, 0.0);
    }
    else if (direction == DOWN) {
        projectiles->position = glm::vec3(position.x, position.y - 1.0, 0.0);
        projectiles->movement = glm::vec3(0.0, -3.0, 0.0);
    }
    else if (direction == RIGHT) {
        projectiles->movement =  glm::vec3(3 * whoIsShooting, 0, 0);
    }
    else if (direction == LEFT) {
        projectiles->movement = glm::vec3(3.0 * whoIsShooting, 0.0, 0.0);
    }
    else if (direction == UPRIGHT) {
        projectiles->movement = glm::vec3(3.0 * whoIsShooting, 3.0, 0.0);
    }
    else if (direction == DOWNRIGHT) {
        projectiles->movement = glm::vec3(3.0 * whoIsShooting, -3.0, 0.0);
    }
    else if (direction == UPLEFT) {
        projectiles->movement = glm::vec3(3.0 * whoIsShooting, 3.0, 0.0);
    }
    else if (direction == DOWNLEFT) {
        projectiles->movement = glm::vec3(3.0 * whoIsShooting, -3.0, 0.0);
    }
    else {
        projectiles->movement = glm::vec3(3 * whoIsShooting, 0, 0);
    }
    projectiles->speed = 5.0f;

    projectiles->height = 0.2f;
    projectiles->width = 0.2f;
    projectiles->entityType = PROJECTILE;
    projectiles->isProj = true;

    if (projectiles->projectileType == BLUE) {
        projectiles->textureID = Util::LoadTexture("Ice.png");
        projectiles->bounces = 1;
        projectiles->speed = 5;
    }

    else if (projectiles->projectileType == RED) {
        projectiles->textureID = Util::LoadTexture("Red.png");
        projectiles->height = 0.6f;
        projectiles->width = 0.6f;
        projectiles->bounces = 0;
        projectiles->speed = 1;
    }

    else if (projectiles->projectileType == GREEN) {
        projectiles->textureID = Util::LoadTexture("Green.png");
        projectiles->height = 0.4f;
        projectiles->width = 0.4f;
        projectiles->bounces = 0;
        projectiles->speed = 2;
    }
}