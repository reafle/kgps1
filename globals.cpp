#include "globals.h"
#include "constants.h"

bool keys[256] = { false } ;
int downX, downY;
bool leftButton = false, middleButton = false, rightButton = false;
bool debugInfo = true;

int linex1 = 0, liney1 = 0, linex2 = 0, liney2 = 0;
int the_matrix[MATRIX_SIZE][MATRIX_SIZE] = { 0 };
