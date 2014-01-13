#include "GL/freeglut.h"
#include "GL/glu.h"
#include <math.h>
#include <time.h>

#include "drawings.h" 
#include "constants.h"
#include "globals.h"

#include <string>
#include <sstream>
#include <math.h>
#include <stdio.h>

std::string debugString;
std::stringstream ss(std::stringstream::in | std::stringstream::out);


void drawScene(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glLoadIdentity();
    glTranslatef(-1, -1, 0);

    glPushMatrix();
    glScalef((GLfloat) 2 / MATRIX_SIZE, (GLfloat) 2 / MATRIX_SIZE, 0);
    glColor3f(0.7f, 0.7f, 0.7f);

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            glPushMatrix();
            glTranslatef((GLfloat) i, (GLfloat) j, 0);
            drawSquareBorder();
            glPopMatrix();
        }
    }

    glPopMatrix();


    /* making sure we have both points set */
    if (linex1 * liney1 * linex2 * liney2 > 0) {
        drawBresenhamLine();
        drawLine();
    }

    drawLinePoints();
    drawDebugInfo();

    glFlush();

}

void drawLinePoints(void) {
    glPushMatrix();

    glPointSize(5);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
        glVertex2f(((GLfloat) linex1 / SQUARE_SIZE) - 0.5f / SQUARE_SIZE, ((GLfloat) liney1 / SQUARE_SIZE) - 0.5f / SQUARE_SIZE);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POINTS);
        glVertex2f(((GLfloat) linex2 / SQUARE_SIZE) - 0.5f / SQUARE_SIZE, ((GLfloat) liney2 / SQUARE_SIZE) - 0.5f / SQUARE_SIZE);
    glEnd();

    glPopMatrix();
}

void drawLine(void) {

    glPushMatrix();

    glPointSize(1);
    glLineWidth(64.0f);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(((GLfloat) linex1 / SQUARE_SIZE) - 0.5f / SQUARE_SIZE, ((GLfloat) liney1 / SQUARE_SIZE) - 0.5f / SQUARE_SIZE, 1);
        glVertex3f(((GLfloat) linex2 / SQUARE_SIZE) - 0.5f / SQUARE_SIZE, ((GLfloat) liney2 / SQUARE_SIZE) - 0.5f / SQUARE_SIZE, 1);
    glEnd();
    glLineWidth(1);
    glPopMatrix();
}

void drawBresenhamLine(void) {
    glPushMatrix();

    glColor3f(1.0f, 0.7f, 0.0f);
    glScalef((GLfloat) 2 / MATRIX_SIZE, (GLfloat) 2 / MATRIX_SIZE, 0);

    float m = linex2 != linex1 ? (liney2 - liney1) / (linex2 - linex1) : 0;

    bool first_octant = linex1 < linex2 && m >= 0 && m <= 1;
    bool second_octant = liney1 < liney2 && m > 1;
    bool third_octant = liney1 < liney2 && m < -1;
    bool fourth_octant = linex2 < linex1 && m >= -1 && m <= 0;
    bool fifth_octant = linex2 < linex1 && m > 0 && m <= 1;
    bool sixth_octant = liney2 < liney1 && m > 1;
    bool seventh_octant = liney2 < liney1 && m < -1;
    bool eight_octant = linex1 < linex2 && m < 0 && m >= -1;

    int x1 = linex1, x2 = linex2;
    int y1 = liney1, y2 = liney2;

    if (fifth_octant || sixth_octant || third_octant || fourth_octant) {
        x1 = linex2;
        x2 = linex1;

        y1 = liney2;
        y2 = liney1;
    }

    int w = x2 - x1;
    int h = y2 - y1;

    int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;
    if (w < 0) dx1 = -1;
    else if (w > 0) dx1 = 1;
    if (h < 0) dy1 = -1;
    else if (h > 0) dy1 = 1;
    if (w < 0) dx2 = -1;
    else if (w > 0) dx2 = 1;

    int longest = abs(w);
    int shortest = abs(h);
    if (!(longest > shortest)) {
        longest = abs(h);
        shortest = abs(w);
        if (h < 0) dy2 = -1;
        else if (h > 0) dy2 = 1;
        dx2 = 0;
    }

    int numerator = longest >> 1;
    int x = x1, y = y1;
    
    for (int i = 0; i <= longest; i++) {

        glPushMatrix();

        drawSquare(x, y);
        numerator += shortest;
        if (!(numerator < longest)) {
            numerator -= longest;
            x += dx1;
            y += dy1;
        } else {
            x += dx2;
            y += dy2;
        }

        glPopMatrix();
    }

    glPopMatrix();
}

void drawSquareBorder(void) {
    glBegin(GL_LINES);

        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);

        glVertex3f(1.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, 1.0f, 0.0f);

        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, 0.0f);

        glVertex3f(0.0f, 1.0f, 0.0f);
        glVertex3f(1.0f, 1.0f, 0.0f);

    glEnd();
}

void drawSquare(int x, int y) {

    glTranslatef(((GLfloat) x - 1), ((GLfloat) y - 1), 0);
    glBegin(GL_TRIANGLES);

        glVertex3f(1.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);

        glVertex3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, 0.0f);

    glEnd();
}

void drawDebugInfo(void) {

    if (debugInfo == true) {

        glPushMatrix();
        glLoadIdentity();

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, SCREEN_X, 0, SCREEN_Y);

        ss.str("");
        ss << "line start : " << linex1 << ", " << liney1 << std::endl;
        ss << "line end : " << linex2 << ", " << liney2 << std::endl;


        debugString = ss.str();
        glColor3f(1.0f, 0.0f, 0.0f);
        glRasterPos2f(20.0f, SCREEN_Y - 20.0f);

        glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*) debugString.c_str());
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }

}