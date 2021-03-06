#ifndef __CALLBACKS__
#define __CALLBACKS__

#include "constants.h"

void CustomKeyboardCallback();
void MouseCallback(int button, int state, int x, int y);
void KeyboardDownCallback(unsigned char ch, int x, int y);
void KeyboardUpCallback(unsigned char ch, int x, int y);
void WindowResizeCallback(int w, int h);
void SceneDisplayCallback(void);

#endif