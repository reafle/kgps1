#include "GL/freeglut.h"
#include "GL/glu.h"
#include <stdio.h>

#include "globals.h"
#include "callbacks.h"
#include "drawings.h"

void CustomKeyboardCallback() {
    if (keys[27]) {
        exit(0);
    }

    glutPostRedisplay();
}

void MouseCallback(int button, int state, int x, int y) {

    downX = x;
    downY = y;

    leftButton = ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN));
    middleButton = ((button == GLUT_MIDDLE_BUTTON) && (state == GLUT_DOWN));
    rightButton = ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN));

    if (leftButton) {
        int old_linex1 = linex1;
        int old_liney1 = liney1;

        linex1 = (GLfloat) (1 + ((int) x / SQUARE_SIZE));
        liney1 = (GLfloat) (MATRIX_SIZE - ((int) y / SQUARE_SIZE));

        if (old_linex1 == linex1 && old_liney1 == liney1) {
            linex1 = 0;
            liney1 = 0;
        }
    }

    if (rightButton) {
        int old_linex2 = linex2;
        int old_liney2 = liney2;

        linex2 = (GLfloat) (1 + ((int) x / SQUARE_SIZE));
        liney2 = (GLfloat) (MATRIX_SIZE - ((int) y / SQUARE_SIZE));

        if (old_linex2 == linex2 && old_liney2 == liney2) {
            linex2 = 0;
            liney2 = 0;
        }

    }

    glutPostRedisplay();
}

void KeyboardDownCallback(unsigned char ch, int x, int y) {
    keys[ch] = true;

    if (ch == 'i') {
        debugInfo = !debugInfo;
    }
}

void KeyboardUpCallback(unsigned char ch, int x, int y) {
    keys[ch] = false;
}

void WindowResizeCallback(int w, int h) {

    double scale, center;
    double windowXmin, windowXmax, windowYmin, windowYmax;

    // Define the portion of the window used for OpenGL rendering.
    glViewport(0, 0, w, h); // View port uses whole window

    // Set up the projection view matrix: orthographic projection
    // Determine the min and max values for x and y that should appear in the window.
    // The complication is that the aspect ratio of the window may not match the
    //		aspect ratio of the scene we want to view.
    w = (w == 0) ? 1 : w;
    h = (h == 0) ? 1 : h;
    if ((Xmax - Xmin) / w < (Ymax - Ymin) / h) {
        scale = ((Ymax - Ymin) / h) / ((Xmax - Xmin) / w);
        center = (Xmax + Xmin) / 2;
        windowXmin = center - (center - Xmin) * scale;
        windowXmax = center + (Xmax - center) * scale;
        windowYmin = Ymin;
        windowYmax = Ymax;
    } else {
        scale = ((Xmax - Xmin) / w) / ((Ymax - Ymin) / h);
        center = (Ymax + Ymin) / 2;
        windowYmin = center - (center - Ymin) * scale;
        windowYmax = center + (Ymax - center) * scale;
        windowXmin = Xmin;
        windowXmax = Xmax;
    }

    // Now that we know the max & min values for x & y that should be visible in the window,
    //		we set up the orthographic projection.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(windowXmin, windowXmax, windowYmin, windowYmax, -1, 1);


}

void SceneDisplayCallback(void) {

    CustomKeyboardCallback();
    drawScene();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}