
#include <graphics/gl.hpp>
#include "scene.hpp"

// void drawScene() {
//     glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     drawGrid();
// }

void drawGrid() {
    glColor3f(0.5f, 0.5f, 0.5f);

    glBegin(GL_LINES);

    for (int i = -20; i <= 20; i++) {
        glVertex3f((float)i, 0.0f, -20.0f);
        glVertex3f((float)i, 0.0f,  20.0f);

        glVertex3f(-20.0f, 0.0f, (float)i);
        glVertex3f( 20.0f, 0.0f, (float)i);
    }

    glEnd();
}