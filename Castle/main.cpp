#define GLFW_INCLUDE_NONE
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define WINDOW_LABEL "Castle"

void processInput(GLFWwindow *window);

// settings
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

// Rotation
static GLfloat yRot = 0.0f;

/* function to reset our viewport after a window resize */
void resizeWindow(GLFWwindow* window, int w, int h )
{
    GLfloat fAspect;  
  
    // Prevent a divide by zero  
    if(h == 0)  
        h = 1;  
  
    // Set Viewport to window dimensions  
    glViewport(0, 0, w, h);  
  
    fAspect = (GLfloat)w/(GLfloat)h;  
  
    // Reset coordinate system  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
  
    // Produce the perspective projection  
    gluPerspective(35.0f, fAspect, 1.0, 40.0);  
  
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  
}

// This function does any needed initialization on the rendering context.  Here it sets up and initializes the lighting for the scene.  
void setupRC(){  

    // Light values and coordinates  
    GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };  
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };  
    GLfloat  lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };  
  
    glEnable(GL_DEPTH_TEST);    // Hidden surface removal  
    glFrontFace(GL_CCW);        // Counter clock-wise polygons face out  
    glEnable(GL_CULL_FACE);     // Do not calculate inside  
  
    // Enable lighting  
    glEnable(GL_LIGHTING);  
  
    // Setup and enable light 0  
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);  
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);  
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);  
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);  
    glEnable(GL_LIGHT0);  
  
    // Enable color tracking  
    glEnable(GL_COLOR_MATERIAL);  
      
    // Set Material properties to follow glColor values  
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  
  
    // Black blue background  
    glClearColor(0.25f, 0.25f, 0.50f, 1.0f);  

}  

/* function to handle key press events */
void handleKeyPress(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) 
        yRot -= 5.0f;  
  
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)  
        yRot += 5.0f;  
                  
    yRot = (GLfloat)((const int)yRot % 360);  

}


void drawFloor (float x_axis, float y_axis)
{
    float x = x_axis / 2.0f;
    float y = y_axis / 2.0f;

    glBegin(GL_QUADS);
        glVertex3f( -x, 0,  y);
        glVertex3f(  x, 0,  y);
        glVertex3f(  x, 0, -y);
        glVertex3f( -x, 0, -y);
    glEnd();
}

void drawFlag(float scale)
{
    float s = scale / 2.0f;

    glBegin(GL_TRIANGLES);
        glVertex3f(0.0f, s, 0.0f);
        glVertex3f(0.0f, -s, 0.0f);
        glVertex3f(3*s, 0.0f, 0.0f);
    glEnd();
}

void drawCuboid(float x_axis, float y_axis, float z_axis)
{
    float x = x_axis / 2.0f;
    float y = y_axis / 2.0f;
    float z = z_axis / 2.0f;

    glBegin(GL_QUADS);

        // frente
        glVertex3f(-x, -z,  y);
        glVertex3f( x, -z,  y);
        glVertex3f( x,  z,  y);
        glVertex3f(-x,  z,  y);

        // trás
        glVertex3f( x, -z, -y);
        glVertex3f(-x, -z, -y);
        glVertex3f(-x,  z, -y);
        glVertex3f( x,  z, -y);

        // esquerda
        glVertex3f(-x, -z, -y);
        glVertex3f(-x, -z,  y);
        glVertex3f(-x,  z,  y);
        glVertex3f(-x,  z, -y);

        // direita
        glVertex3f(x, -z,  y);
        glVertex3f(x, -z, -y);
        glVertex3f(x,  z, -y);
        glVertex3f(x,  z,  y);

        // cima
        glVertex3f(-x, z,  y);
        glVertex3f( x, z,  y);
        glVertex3f( x, z, -y);
        glVertex3f(-x, z, -y);

        // baixo
        glVertex3f(-x, -z, -y);
        glVertex3f( x, -z, -y);
        glVertex3f( x, -z,  y);
        glVertex3f(-x, -z,  y);

    glEnd();
}


/* Here goes our drawing code */
void drawGLScene(GLFWwindow* window)
{
    GLUquadricObj *pObj;    // Quadric Object  
      
    // Clear the window with current clearing color  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  
    // Save the matrix state and do the rotations  
    glPushMatrix();

	// Move object back and do in place rotation  
	glTranslatef(0.0f, -1.0f, -5.0f);  
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(0.0f, 0.0f, 0.0f, 0.0f);    

	// Draw something  
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);  

	// floor (green)
	glColor3f(0.0f, 0.6f, 0.0f);  
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
        drawFloor(10.0f, 10.0f);
	glPopMatrix();

    // castle cuboids

    //right wall
	glColor3f(0.9f, 0.9f, 0.9f);  
	glPushMatrix();
		glTranslatef(0.85f, 0.0f, 0.0f);
        drawCuboid(0.3f, 2.0f, 1.5f);
	glPopMatrix();

    //left wall
	glColor3f(0.9f, 0.9f, 0.9f);  
	glPushMatrix();
		glTranslatef(-0.85f, 0.0f, 0.0f);
        drawCuboid(0.3f, 2.0f, 1.5f);
	glPopMatrix();
    
    //back wall
	glColor3f(0.9f, 0.9f, 0.9f);  
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, -1.0f);
        drawCuboid(2.0f, 0.4f, 1.5f);
	glPopMatrix();

    //left front wall
	glColor3f(0.9f, 0.9f, 0.9f);  
	glPushMatrix();
		glTranslatef(-0.4f, 0.0f, 0.75f);
        drawCuboid(0.5f, 0.4f, 1.5f);
	glPopMatrix();

    //right front wall
	glColor3f(0.9f, 0.9f, 0.9f);  
	glPushMatrix();
		glTranslatef(0.4f, 0.0f, 0.75f);
        drawCuboid(0.5f, 0.4f, 1.5f);
	glPopMatrix();

    // top wall
	glColor3f(1.0f, 1.0f, 1.0f); 
	glPushMatrix();
		glTranslatef(0.0f, 0.7f, -0.1f);
        drawCuboid(2.1f, 2.3f, 0.2f);
	glPopMatrix();

    //left front tower
	glColor3f(0.9f, 0.9f, 0.9f);  
	glPushMatrix();
		glTranslatef(-0.9f, 1.0f, 0.9f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.25f, 0.25f, 4.0f, 26, 13);
	glPopMatrix(); 
    
    //right front tower
    glColor3f(0.9f, 0.9f, 0.9f);  
	glPushMatrix();
		glTranslatef(0.9f, 1.0f, 0.9f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.25f, 0.25f, 4.0f, 26, 13);
	glPopMatrix();  
    
    //left front cone
    glColor3f(1.0f, 0.0f, 0.0f);  
	glPushMatrix();
		glTranslatef(-0.9f, 1.5f, 0.9f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.0f, 0.3f, 0.5f, 26, 13);
	glPopMatrix();

    //right front cone
    glColor3f(1.0f, 0.0f, 0.0f);  
	glPushMatrix();
		glTranslatef(0.9f, 1.5f, 0.9f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.0f, 0.3f, 0.5f, 26, 13);
	glPopMatrix();
    
    //central tower
    glColor3f(0.9f, 0.9f, 0.9f);  
	glPushMatrix();
		glTranslatef(0.0f, 1.4f, -0.3f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.4f, 0.4f, 2.0f, 26, 13);
	glPopMatrix();

    //central cone
    glColor3f(1.0f, 0.0f, 0.0f);  
	glPushMatrix();
		glTranslatef(0.0f, 2.0f, -0.3f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.0f, 0.5f, 0.7f, 26, 13);
	glPopMatrix();

    //left back tower
	glColor3f(0.9f, 0.9f, 0.9f);  
	glPushMatrix();
		glTranslatef(-0.9f, 1.0f, -1.1f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.25f, 0.25f, 4.0f, 26, 13);
	glPopMatrix(); 
    
    //right back tower
    glColor3f(0.9f, 0.9f, 0.9f);  
	glPushMatrix();
		glTranslatef(0.9f, 1.0f, -1.1f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.25f, 0.25f, 4.0f, 26, 13);
	glPopMatrix();  
    
    //left back cone
    glColor3f(1.0f, 0.0f, 0.0f);  
	glPushMatrix();
		glTranslatef(-0.9f, 1.5f, -1.1f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.0f, 0.3f, 0.5f, 26, 13);
	glPopMatrix();

    //right back cone
    glColor3f(1.0f, 0.0f, 0.0f);  
	glPushMatrix();
		glTranslatef(0.9f, 1.5f, -1.1f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.0f, 0.3f, 0.5f, 26, 13);
	glPopMatrix();

    //central flag
    glColor3f(1.0f, 0.0f, 0.0f);  
	glPushMatrix();
		glTranslatef(0.0f, 2.2f, -0.3f);
        drawFlag(0.35f);
	glPopMatrix();

    //central flagpole
    glColor3f(0.3f, 0.3f, 0.3f);  
	glPushMatrix();
		glTranslatef(0.0f, 2.38f, -0.3f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.02f, 0.02f, 0.7f, 26, 13);
	glPopMatrix();

    //front righ flag
    glColor3f(1.0f, 0.0f, 0.0f);  
	glPushMatrix();
		glTranslatef(0.9f, 1.7f, 0.9f);
        drawFlag(0.2f);
	glPopMatrix();

    //flont right flagpole
    glColor3f(0.3f, 0.3f, 0.3f);  
	glPushMatrix();
		glTranslatef(0.9f, 1.8f, 0.9f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.015f, 0.015f, 0.7f, 26, 13);
	glPopMatrix();

    //front left flag
    glColor3f(1.0f, 0.0f, 0.0f);  
	glPushMatrix();
		glTranslatef(-0.9f, 1.7f, 0.9f);
        drawFlag(0.2f);
	glPopMatrix();

    //flont left flagpole
    glColor3f(0.3f, 0.3f, 0.3f);  
	glPushMatrix();
		glTranslatef(-0.9f, 1.8f, 0.9f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.015f, 0.015f, 0.7f, 26, 13);
	glPopMatrix();


    //back righ flag
    glColor3f(1.0f, 0.0f, 0.0f);  
	glPushMatrix();
		glTranslatef(0.9f, 1.7f, -1.1f);
        drawFlag(0.2f);
	glPopMatrix();

    //back right flagpole
    glColor3f(0.3f, 0.3f, 0.3f);  
	glPushMatrix();
		glTranslatef(0.9f, 1.8f, -1.1f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.015f, 0.015f, 0.7f, 26, 13);
	glPopMatrix();

    //back left flag
    glColor3f(1.0f, 0.0f, 0.0f);  
	glPushMatrix();
		glTranslatef(-0.9f, 1.7f, -1.1f);
        drawFlag(0.2f);
	glPopMatrix();

    //back left flagpole
    glColor3f(0.3f, 0.3f, 0.3f);  
	glPushMatrix();
		glTranslatef(-0.9f, 1.8f, -1.1f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.015f, 0.015f, 0.7f, 26, 13);
	glPopMatrix();


    // Restore the matrix state  
    glPopMatrix();  
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_LABEL, nullptr, nullptr);
    if (window == nullptr)
    {
        printf("Failed to open GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resizeWindow);
    glfwSwapInterval(1);
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    resizeWindow(window, SCREEN_WIDTH, SCREEN_HEIGHT);
    setupRC();

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        handleKeyPress(window);

        // render
        drawGLScene(window);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// void drawCube(float size)
// {
//     float s = size / 2.0f;

//     glBegin(GL_QUADS);

//         // frente
//         glVertex3f(-s, -s,  s);
//         glVertex3f( s, -s,  s);
//         glVertex3f( s,  s,  s);
//         glVertex3f(-s,  s,  s);

//         // trás
//         glVertex3f( s, -s, -s);
//         glVertex3f(-s, -s, -s);
//         glVertex3f(-s,  s, -s);
//         glVertex3f( s,  s, -s);

//         // esquerda
//         glVertex3f(-s, -s, -s);
//         glVertex3f(-s, -s,  s);
//         glVertex3f(-s,  s,  s);
//         glVertex3f(-s,  s, -s);

//         // direita
//         glVertex3f(s, -s,  s);
//         glVertex3f(s, -s, -s);
//         glVertex3f(s,  s, -s);
//         glVertex3f(s,  s,  s);

//         // cima
//         glVertex3f(-s, s,  s);
//         glVertex3f( s, s,  s);
//         glVertex3f( s, s, -s);
//         glVertex3f(-s, s, -s);

//         // baixo
//         glVertex3f(-s, -s, -s);
//         glVertex3f( s, -s, -s);
//         glVertex3f( s, -s,  s);
//         glVertex3f(-s, -s,  s);

//     glEnd();
// }