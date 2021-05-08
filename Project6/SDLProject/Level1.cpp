#include "Level1.h"
#include <iostream>
using namespace std;

#define LEVEL1_WIDTH 368
#define LEVEL1_HEIGHT 8
#define LEVEL1_ENEMYCOUNT 45
unsigned int level1_data[] =
{
 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2,
 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2,
 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2,
 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 2,
 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2,
 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2,
 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
};

void Level1::Initialize() {
	// Move over all of the player and enemy code from initialization.
    // Inside of Initialize

    state.nextScene = -1;

    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 4, 1);
    // Initialize Game Objects

    // Initialize Player
    state.player = new Entity();
    state.player->setType(0);
    state.player->position = glm::vec3(5.0, -5.0, 0.0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, 0.0, 0);
    state.player->speed = 5.0f;
    state.player->textureID = Util::LoadTexture("rat.png");
    state.player->height = 0.5f;
    state.player->width = 0.5f;
    state.player->entityType = PLAYER;
    state.player->enemiesToDefeat = LEVEL1_ENEMYCOUNT;
    state.player->animIndices = new int[4]{0 , 1, 2, 3 };
    state.player->animRight = new int[4]{ 0, 1, 2, 3 };
    state.player->animUp = new int[4]{ 8, 9, 10, 11 };
    state.player->animLeft = new int[4]{ 0, 1, 2, 3 };
    state.player->animDown = new int[4]{ 4, 5, 6, 7 };
    state.player->animFrames = 4;
    state.player->animIndex = 0;
    state.player->animTime = 0;
    state.player->projectileType = GREEN;


    state.lives = 5;
    state.player->lives = state.lives;
    state.enemies = new Entity[LEVEL1_ENEMYCOUNT];
    GLuint bearTextureID = Util::LoadTexture("bear.png");
    GLuint birdTextureID = Util::LoadTexture("bird.png");
    GLuint snakeTextureID = Util::LoadTexture("snake.png");

    state.enemies[0].textureID = bearTextureID;
    state.enemies[0].position = glm::vec3(10.0, -3, 0.0);
    state.enemies[0].jumpTimer = 2.5f;
    state.enemies[0].speed = 2.0f;
    state.enemies[0].aiType = BEAR;
    state.enemies[0].projectileType = GREEN;
    state.enemies[0].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[0].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[0].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[0].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[0].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[0].animFrames = 4;
    state.enemies[0].animIndex = 0;
    state.enemies[0].animTime = 0;

    state.enemies[1].textureID = birdTextureID;
    state.enemies[1].position = glm::vec3(11.0, -6, 0.0);
    state.enemies[1].jumpTimer = 2.5f;
    state.enemies[1].speed = 2.0f;
    state.enemies[1].aiType = BIRD;
    state.enemies[1].projectileType = BLUE;
    state.enemies[1].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[1].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[1].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[1].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[1].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[1].animFrames = 4;
    state.enemies[1].animIndex = 0;
    state.enemies[1].animTime = 0;

    state.enemies[2].textureID = snakeTextureID;
    state.enemies[2].position = glm::vec3(7, -6, 0.0);
    state.enemies[2].jumpTimer = 2.5f;
    state.enemies[2].speed = 1.0f;
    state.enemies[2].aiType = SNAKE;
    state.enemies[2].projectileType = RED;
    state.enemies[2].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[2].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[2].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[2].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[2].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[2].animFrames = 4;
    state.enemies[2].animIndex = 0;
    state.enemies[2].animTime = 0;

    state.enemies[3].textureID = bearTextureID;
    state.enemies[3].position = glm::vec3(25, -4, 0.0);
    state.enemies[3].jumpTimer = 2.5f;
    state.enemies[3].speed = 2.0f;
    state.enemies[3].aiType = BEAR;
    state.enemies[3].projectileType = GREEN;
    state.enemies[3].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[3].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[3].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[3].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[3].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[3].animFrames = 4;
    state.enemies[3].animIndex = 0;
    state.enemies[3].animTime = 0;

    state.enemies[4].textureID = birdTextureID;
    state.enemies[4].position = glm::vec3(30, -1, 0.0);
    state.enemies[4].jumpTimer = 2.5f;
    state.enemies[4].speed = 2.0f;
    state.enemies[4].aiType = BIRD;
    state.enemies[4].projectileType = BLUE;
    state.enemies[4].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[4].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[4].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[4].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[4].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[4].animFrames = 4;
    state.enemies[4].animIndex = 0;
    state.enemies[4].animTime = 0;

    state.enemies[5].textureID = snakeTextureID;
    state.enemies[5].position = glm::vec3(35, -5, 0.0);
    state.enemies[5].jumpTimer = 2.5f;
    state.enemies[5].speed = 1.0f;
    state.enemies[5].aiType = SNAKE;
    state.enemies[5].projectileType = RED;
    state.enemies[5].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[5].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[5].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[5].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[5].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[5].animFrames = 4;
    state.enemies[5].animIndex = 0;
    state.enemies[5].animTime = 0;

    state.enemies[6].textureID = bearTextureID;
    state.enemies[6].position = glm::vec3(42, -1, 0.0);
    state.enemies[6].jumpTimer = 2.5f;
    state.enemies[6].speed = 2.0f;
    state.enemies[6].aiType = BEAR;
    state.enemies[6].projectileType = GREEN;
    state.enemies[6].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[6].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[6].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[6].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[6].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[6].animFrames = 4;
    state.enemies[6].animIndex = 0;
    state.enemies[6].animTime = 0;

    state.enemies[7].textureID = birdTextureID;
    state.enemies[7].position = glm::vec3(56, -4, 0.0);
    state.enemies[7].jumpTimer = 2.5f;
    state.enemies[7].speed = 1.0f;
    state.enemies[7].aiType = BIRD;
    state.enemies[7].projectileType = BLUE;
    state.enemies[7].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[7].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[7].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[7].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[7].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[7].animFrames = 4;
    state.enemies[7].animIndex = 0;
    state.enemies[7].animTime = 0;

    state.enemies[8].textureID = snakeTextureID;
    state.enemies[8].position = glm::vec3(61, -2, 0.0);
    state.enemies[8].jumpTimer = 2.5f;
    state.enemies[8].speed = 1.0f;
    state.enemies[8].aiType = SNAKE;
    state.enemies[8].projectileType = RED;
    state.enemies[8].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[8].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[8].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[8].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[8].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[8].animFrames = 4;
    state.enemies[8].animIndex = 0;
    state.enemies[8].animTime = 0;

    state.enemies[9].textureID = bearTextureID;
    state.enemies[9].position = glm::vec3(61, -4, 0.0);
    state.enemies[9].jumpTimer = 2.5f;
    state.enemies[9].speed = 2.0f;
    state.enemies[9].aiType = BEAR;
    state.enemies[9].projectileType = GREEN;
    state.enemies[9].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[9].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[9].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[9].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[9].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[9].animFrames = 4;
    state.enemies[9].animIndex = 0;
    state.enemies[9].animTime = 0;

    state.enemies[10].textureID = birdTextureID;
    state.enemies[10].position = glm::vec3(75, -5, 0.0);
    state.enemies[10].jumpTimer = 2.5f;
    state.enemies[10].speed = 1.0f;
    state.enemies[10].aiType = BIRD;
    state.enemies[10].projectileType = BLUE;
    state.enemies[10].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[10].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[10].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[10].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[10].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[10].animFrames = 4;
    state.enemies[10].animIndex = 0;
    state.enemies[10].animTime = 0;

    state.enemies[11].textureID = snakeTextureID;
    state.enemies[11].position = glm::vec3(75, -2, 0.0);
    state.enemies[11].jumpTimer = 2.5f;
    state.enemies[11].speed = 1.0f;
    state.enemies[11].aiType = SNAKE;
    state.enemies[11].projectileType = RED;
    state.enemies[11].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[11].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[11].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[11].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[11].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[11].animFrames = 4;
    state.enemies[11].animIndex = 0;
    state.enemies[11].animTime = 0;

    state.enemies[12].textureID = bearTextureID;
    state.enemies[12].position = glm::vec3(80, -3.5, 0.0);
    state.enemies[12].jumpTimer = 2.5f;
    state.enemies[12].speed = 2.0f;
    state.enemies[12].aiType = BEAR;
    state.enemies[12].projectileType = GREEN;
    state.enemies[12].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[12].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[12].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[12].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[12].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[12].animFrames = 4;
    state.enemies[12].animIndex = 0;
    state.enemies[12].animTime = 0;

    state.enemies[13].textureID = birdTextureID;
    state.enemies[13].position = glm::vec3(84, -2.5, 0.0);
    state.enemies[13].jumpTimer = 2.5f;
    state.enemies[13].speed = 1.0f;
    state.enemies[13].aiType = BIRD;
    state.enemies[13].projectileType = BLUE;
    state.enemies[13].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[13].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[13].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[13].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[13].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[13].animFrames = 4;
    state.enemies[13].animIndex = 0;
    state.enemies[13].animTime = 0;

    state.enemies[14].textureID = snakeTextureID;
    state.enemies[14].position = glm::vec3(84, -4.5, 0.0);
    state.enemies[14].jumpTimer = 2.5f;
    state.enemies[14].speed = 1.0f;
    state.enemies[14].aiType = SNAKE;
    state.enemies[14].projectileType = RED;
    state.enemies[14].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[14].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[14].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[14].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[14].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[14].animFrames = 4;
    state.enemies[14].animIndex = 0;
    state.enemies[14].animTime = 0;

    state.enemies[15].textureID = bearTextureID;
    state.enemies[15].position = glm::vec3(90, -5.2, 0.0);
    state.enemies[15].jumpTimer = 2.5f;
    state.enemies[15].speed = 2.0f;
    state.enemies[15].aiType = BEAR;
    state.enemies[15].projectileType = GREEN;
    state.enemies[15].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[15].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[15].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[15].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[15].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[15].animFrames = 4;
    state.enemies[15].animIndex = 0;
    state.enemies[15].animTime = 0;

    state.enemies[16].textureID = birdTextureID;
    state.enemies[16].position = glm::vec3(105, -3.3, 0.0);
    state.enemies[16].jumpTimer = 2.5f;
    state.enemies[16].speed = 1.0f;
    state.enemies[16].aiType = BIRD;
    state.enemies[16].projectileType = BLUE;
    state.enemies[16].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[16].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[16].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[16].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[16].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[16].animFrames = 4;
    state.enemies[16].animIndex = 0;
    state.enemies[16].animTime = 0;

    state.enemies[17].textureID = snakeTextureID;
    state.enemies[17].position = glm::vec3(120, -1.5, 0.0);
    state.enemies[17].jumpTimer = 2.5f;
    state.enemies[17].speed = 1.0f;
    state.enemies[17].aiType = SNAKE;
    state.enemies[17].projectileType = RED;
    state.enemies[17].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[17].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[17].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[17].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[17].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[17].animFrames = 4;
    state.enemies[17].animIndex = 0;
    state.enemies[17].animTime = 0;

    state.enemies[18].textureID = bearTextureID;
    state.enemies[18].position = glm::vec3(135, -3.2, 0.0);
    state.enemies[18].jumpTimer = 2.5f;
    state.enemies[18].speed = 2.0f;
    state.enemies[18].aiType = BEAR;
    state.enemies[18].projectileType = GREEN;
    state.enemies[18].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[18].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[18].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[18].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[18].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[18].animFrames = 4;
    state.enemies[18].animIndex = 0;
    state.enemies[18].animTime = 0;

    state.enemies[19].textureID = birdTextureID;
    state.enemies[19].position = glm::vec3(146, -2.5, 0.0);
    state.enemies[19].jumpTimer = 2.5f;
    state.enemies[19].speed = 1.0f;
    state.enemies[19].aiType = BIRD;
    state.enemies[19].projectileType = BLUE;
    state.enemies[19].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[19].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[19].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[19].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[19].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[19].animFrames = 4;
    state.enemies[19].animIndex = 0;
    state.enemies[19].animTime = 0;

    state.enemies[20].textureID = snakeTextureID;
    state.enemies[20].position = glm::vec3(157, -4.7, 0.0);
    state.enemies[20].jumpTimer = 2.5f;
    state.enemies[20].speed = 1.0f;
    state.enemies[20].aiType = SNAKE;
    state.enemies[20].projectileType = RED;
    state.enemies[20].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[20].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[20].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[20].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[20].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[20].animFrames = 4;
    state.enemies[20].animIndex = 0;
    state.enemies[20].animTime = 0;

    state.enemies[21].textureID = bearTextureID;
    state.enemies[21].position = glm::vec3(170, -5.0, 0.0);
    state.enemies[21].jumpTimer = 2.5f;
    state.enemies[21].speed = 2.0f;
    state.enemies[21].aiType = BEAR;
    state.enemies[21].projectileType = GREEN;
    state.enemies[21].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[21].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[21].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[21].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[21].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[21].animFrames = 4;
    state.enemies[21].animIndex = 0;
    state.enemies[21].animTime = 0;

    state.enemies[22].textureID = snakeTextureID;
    state.enemies[22].position = glm::vec3(170, -1.72, 0.0);
    state.enemies[22].jumpTimer = 2.5f;
    state.enemies[22].speed = 1.0f;
    state.enemies[22].aiType = SNAKE;
    state.enemies[22].projectileType = RED;
    state.enemies[22].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[22].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[22].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[22].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[22].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[22].animFrames = 4;
    state.enemies[22].animIndex = 0;
    state.enemies[22].animTime = 0;

    state.enemies[23].textureID = snakeTextureID;
    state.enemies[23].position = glm::vec3(178, -3.1, 0.0);
    state.enemies[23].jumpTimer = 2.5f;
    state.enemies[23].speed = 1.0f;
    state.enemies[23].aiType = SNAKE;
    state.enemies[23].projectileType = RED;
    state.enemies[23].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[23].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[23].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[23].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[23].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[23].animFrames = 4;
    state.enemies[23].animIndex = 0;
    state.enemies[23].animTime = 0;

    state.enemies[24].textureID = bearTextureID;
    state.enemies[24].position = glm::vec3(185.0, -3.8, 0.0);
    state.enemies[24].jumpTimer = 2.5f;
    state.enemies[24].speed = 2.0f;
    state.enemies[24].aiType = BEAR;
    state.enemies[24].projectileType = GREEN;
    state.enemies[24].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[24].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[24].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[24].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[24].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[24].animFrames = 4;
    state.enemies[24].animIndex = 0;
    state.enemies[24].animTime = 0;

    state.enemies[25].textureID = birdTextureID;
    state.enemies[25].position = glm::vec3(194.0, -3.8, 0.0);
    state.enemies[25].jumpTimer = 2.5f;
    state.enemies[25].speed = 2.0f;
    state.enemies[25].aiType = BIRD;
    state.enemies[25].projectileType = BLUE;
    state.enemies[25].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[25].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[25].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[25].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[25].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[25].animFrames = 4;
    state.enemies[25].animIndex = 0;
    state.enemies[25].animTime = 0;

    state.enemies[26].textureID = snakeTextureID;
    state.enemies[26].position = glm::vec3(202, -2.6, 0.0);
    state.enemies[26].jumpTimer = 2.5f;
    state.enemies[26].speed = 1.0f;
    state.enemies[26].aiType = SNAKE;
    state.enemies[26].projectileType = RED;
    state.enemies[26].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[26].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[26].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[26].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[26].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[26].animFrames = 4;
    state.enemies[26].animIndex = 0;
    state.enemies[26].animTime = 0;

    state.enemies[27].textureID = bearTextureID;
    state.enemies[27].position = glm::vec3(210, -1.9, 0.0);
    state.enemies[27].jumpTimer = 2.5f;
    state.enemies[27].speed = 2.0f;
    state.enemies[27].aiType = BEAR;
    state.enemies[27].projectileType = GREEN;
    state.enemies[27].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[27].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[28].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[28].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[28].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[28].animFrames = 4;
    state.enemies[28].animIndex = 0;
    state.enemies[28].animTime = 0;

    state.enemies[29].textureID = birdTextureID;
    state.enemies[29].position = glm::vec3(210, -4.8, 0.0);
    state.enemies[29].jumpTimer = 2.5f;
    state.enemies[29].speed = 2.0f;
    state.enemies[29].aiType = BIRD;
    state.enemies[29].projectileType = BLUE;
    state.enemies[29].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[29].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[29].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[29].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[29].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[29].animFrames = 4;
    state.enemies[29].animIndex = 0;
    state.enemies[29].animTime = 0;

    state.enemies[30].textureID = snakeTextureID;
    state.enemies[30].position = glm::vec3(227, -2.0, 0.0);
    state.enemies[30].jumpTimer = 2.5f;
    state.enemies[30].speed = 1.0f;
    state.enemies[30].aiType = SNAKE;
    state.enemies[30].projectileType = RED;
    state.enemies[30].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[30].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[30].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[30].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[30].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[30].animFrames = 4;
    state.enemies[30].animIndex = 0;
    state.enemies[30].animTime = 0;

    state.enemies[31].textureID = bearTextureID;
    state.enemies[31].position = glm::vec3(232, -5.2, 0.0);
    state.enemies[31].jumpTimer = 2.5f;
    state.enemies[31].speed = 2.0f;
    state.enemies[31].aiType = BEAR;
    state.enemies[31].projectileType = GREEN;
    state.enemies[31].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[31].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[31].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[31].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[31].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[31].animFrames = 4;
    state.enemies[31].animIndex = 0;
    state.enemies[31].animTime = 0;

    state.enemies[32].textureID = birdTextureID;
    state.enemies[32].position = glm::vec3(240, -1.2, 0.0);
    state.enemies[32].jumpTimer = 2.5f;
    state.enemies[32].speed = 1.0f;
    state.enemies[32].aiType = BIRD;
    state.enemies[32].projectileType = BLUE;
    state.enemies[32].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[32].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[32].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[32].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[32].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[32].animFrames = 4;
    state.enemies[32].animIndex = 0;
    state.enemies[32].animTime = 0;

    state.enemies[33].textureID = snakeTextureID;
    state.enemies[33].position = glm::vec3(247, -3.5, 0.0);
    state.enemies[33].jumpTimer = 2.5f;
    state.enemies[33].speed = 1.0f;
    state.enemies[33].aiType = SNAKE;
    state.enemies[33].projectileType = RED;
    state.enemies[33].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[33].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[33].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[33].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[33].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[33].animFrames = 4;
    state.enemies[33].animIndex = 0;
    state.enemies[33].animTime = 0;

    state.enemies[34].textureID = bearTextureID;
    state.enemies[34].position = glm::vec3(266, -1.5, 0.0);
    state.enemies[34].jumpTimer = 2.5f;
    state.enemies[34].speed = 2.0f;
    state.enemies[34].aiType = BEAR;
    state.enemies[34].projectileType = GREEN;
    state.enemies[34].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[34].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[34].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[34].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[34].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[34].animFrames = 4;
    state.enemies[34].animIndex = 0;
    state.enemies[34].animTime = 0;

    state.enemies[35].textureID = birdTextureID;
    state.enemies[35].position = glm::vec3(277, -3.5, 0.0);
    state.enemies[35].jumpTimer = 2.5f;
    state.enemies[35].speed = 1.0f;
    state.enemies[35].aiType = BIRD;
    state.enemies[35].projectileType = BLUE;
    state.enemies[35].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[35].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[35].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[35].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[35].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[35].animFrames = 4;
    state.enemies[35].animIndex = 0;
    state.enemies[35].animTime = 0;

    state.enemies[36].textureID = snakeTextureID;
    state.enemies[36].position = glm::vec3(280, -1.6, 0.0);
    state.enemies[36].jumpTimer = 2.5f;
    state.enemies[36].speed = 1.0f;
    state.enemies[36].aiType = SNAKE;
    state.enemies[36].projectileType = RED;
    state.enemies[36].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[36].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[36].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[36].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[36].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[36].animFrames = 4;
    state.enemies[36].animIndex = 0;
    state.enemies[36].animTime = 0;

    state.enemies[37].textureID = bearTextureID;
    state.enemies[37].position = glm::vec3(280, -4.5, 0.0);
    state.enemies[37].jumpTimer = 2.5f;
    state.enemies[37].speed = 2.0f;
    state.enemies[37].aiType = BEAR;
    state.enemies[37].projectileType = GREEN;
    state.enemies[37].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[37].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[37].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[37].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[37].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[37].animFrames = 4;
    state.enemies[37].animIndex = 0;
    state.enemies[37].animTime = 0;

    state.enemies[38].textureID = birdTextureID;
    state.enemies[38].position = glm::vec3(295, -4.5, 0.0);
    state.enemies[38].jumpTimer = 2.5f;
    state.enemies[38].speed = 1.0f;
    state.enemies[38].aiType = BIRD;
    state.enemies[38].projectileType = BLUE;
    state.enemies[38].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[38].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[38].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[38].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[38].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[38].animFrames = 4;
    state.enemies[38].animIndex = 0;
    state.enemies[38].animTime = 0;

    state.enemies[39].textureID = snakeTextureID;
    state.enemies[39].position = glm::vec3(300, -5.0, 0.0);
    state.enemies[39].jumpTimer = 2.5f;
    state.enemies[39].speed = 1.0f;
    state.enemies[39].aiType = SNAKE;
    state.enemies[39].projectileType = RED;
    state.enemies[39].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[39].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[39].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[39].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[39].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[39].animFrames = 4;
    state.enemies[39].animIndex = 0;
    state.enemies[39].animTime = 0;

    state.enemies[40].textureID = bearTextureID;
    state.enemies[40].position = glm::vec3(310, -2.5, 0.0);
    state.enemies[40].jumpTimer = 2.5f;
    state.enemies[40].speed = 2.0f;
    state.enemies[40].aiType = BEAR;
    state.enemies[40].projectileType = GREEN;
    state.enemies[40].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[40].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[40].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[40].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[40].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[40].animFrames = 4;
    state.enemies[40].animIndex = 0;
    state.enemies[40].animTime = 0;

    state.enemies[41].textureID = birdTextureID;
    state.enemies[41].position = glm::vec3(323, -3.3, 0.0);
    state.enemies[41].jumpTimer = 2.5f;
    state.enemies[41].speed = 1.0f;
    state.enemies[41].aiType = BIRD;
    state.enemies[41].projectileType = BLUE;
    state.enemies[41].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[41].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[41].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[41].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[41].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[41].animFrames = 4;
    state.enemies[41].animIndex = 0;
    state.enemies[41].animTime = 0;

    state.enemies[42].textureID = snakeTextureID;
    state.enemies[42].position = glm::vec3(338, -3.2, 0.0);
    state.enemies[42].jumpTimer = 2.5f;
    state.enemies[42].speed = 1.0f;
    state.enemies[42].aiType = SNAKE;
    state.enemies[42].projectileType = RED;
    state.enemies[42].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[42].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[42].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[42].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[42].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[42].animFrames = 4;
    state.enemies[42].animIndex = 0;
    state.enemies[42].animTime = 0;

    state.enemies[43].textureID = bearTextureID;
    state.enemies[43].position = glm::vec3(352, -3.5, 0.0);
    state.enemies[43].jumpTimer = 2.5f;
    state.enemies[43].speed = 2.0f;
    state.enemies[43].aiType = BEAR;
    state.enemies[43].projectileType = GREEN;
    state.enemies[43].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[43].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[43].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[43].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[43].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[43].animFrames = 4;
    state.enemies[43].animIndex = 0;
    state.enemies[43].animTime = 0;

    state.enemies[44].textureID = birdTextureID;
    state.enemies[44].position = glm::vec3(360, -3.5, 0.0);
    state.enemies[44].jumpTimer = 2.5f;
    state.enemies[44].speed = 1.0f;
    state.enemies[44].aiType = BIRD;
    state.enemies[44].projectileType = BLUE;
    state.enemies[44].animIndices = new int[4]{ 0 , 1, 2, 3 };
    state.enemies[44].animRight = new int[4]{ 0, 1, 2, 3 };
    state.enemies[44].animUp = new int[4]{ 8, 9, 10, 11 };
    state.enemies[44].animLeft = new int[4]{ 0, 1, 2, 3 };
    state.enemies[44].animDown = new int[4]{ 4, 5, 6, 7 };
    state.enemies[44].animFrames = 4;
    state.enemies[44].animIndex = 0;
    state.enemies[44].animTime = 0;

    for (int i = 0; i < LEVEL1_ENEMYCOUNT; i++) {
        state.enemies[i].acceleration = glm::vec3(0.0, -9.0, 0.0);
        state.enemies[i].speed = 1.0f;
        state.enemies[i].entityType = ENEMY;
        state.enemies[i].Update(0, state.player, NULL, 0, state.map);
        state.enemies[i].width = 0.8;
        state.enemies[i].height = 0.8;
        state.enemies[i].aiState = IDLE;
    }
}
void Level1::Update(float deltaTime) {

    for (int i = 0; i < LEVEL1_ENEMYCOUNT; i++) {
        if (state.enemies[i].projectiles != NULL) {
            state.enemies[i].projectiles->Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMYCOUNT, state.map);
        }
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMYCOUNT, state.map);
        //state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMYCOUNT, state.map);
    }

    if (state.player->projectiles != NULL) {
        state.player->projectiles->Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMYCOUNT, state.map);
    }

    state.player->Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMYCOUNT, state.map);
    if (state.player->position.y < -8) {
        state.player->lives -= 1;
        state.player->lostLifeFlag = true;
        state.player->position = glm::vec3(5.0, 0.0, 0.0);
        if (state.player->lives == 0) {
            state.player->isActive = false;
        }
    }
    if (state.player->position.x >= 364.25) {
        finished = true;
        state.lives = state.player->lives;
    }
}
int Level1::Render(ShaderProgram* program) {
   

    if (state.player->isActive == false) {
        return 1;
    }

    if (finished == true) {
        return 2;
    }

	state.map->Render(program);
    if (state.player->projectiles != NULL) {
        state.player->projectiles->Render(program);
    }
	state.player->Render(program);


    for (int i = 0; i < LEVEL1_ENEMYCOUNT; i++) {
        if (state.enemies[i].projectiles != NULL) {
            state.enemies[i].projectiles->Render(program);
        }
        state.enemies[i].Render(program);
    }

    Util::DrawText(program, fontTextureID, to_string(state.player->lives), 0.4f, 0.01f, glm::vec3(state.player->position.x - 0.6, state.player->position.y + 0.3, 0));
    if (state.player->projectileType == RED) {
        Util::DrawText(program, fontTextureID, "R", 0.4f, 0.01f, glm::vec3(state.player->position.x - 0.6, state.player->position.y - 0.4, 0));
    }

    else if (state.player->projectileType == GREEN) {
        Util::DrawText(program, fontTextureID, "G", 0.4f, 0.01f, glm::vec3(state.player->position.x - 0.6, state.player->position.y - 0.4, 0));
    }

    else if (state.player->projectileType == BLUE) {
        Util::DrawText(program, fontTextureID, "B", 0.4f, 0.01f, glm::vec3(state.player->position.x - 0.6, state.player->position.y - 0.4, 0));
    }
    return 0;
}