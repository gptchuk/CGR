#define GLFW_INCLUDE_NONE
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define WINDOW_LABEL "Snowman"

void processInput(GLFWwindow *window);

// settings
#define SCREEN_WIDTH  600
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


void drawScarfTie (float top, float base, float height, float depth)
{
    float t = top / 2.0f;
    float b = base / 2.0f;
    float h = height / 2.0f;
    float d = depth / 2.0f;

    glBegin(GL_QUADS);

        // frente
        glVertex3f(-b, -h,  d);
        glVertex3f( b, -h,  d);
        glVertex3f( t,  h,  d);
        glVertex3f(-t,  h,  d);
        
        // trás
        glVertex3f( b, -h, -d);
        glVertex3f(-b, -h, -d);
        glVertex3f(-t,  h, -d);
        glVertex3f( t,  h, -d);

        // esquerda
        glVertex3f(-b, -h, -d);
        glVertex3f(-b, -h,  d);
        glVertex3f(-t,  h,  d);
        glVertex3f(-t,  h, -d);

        // direita
        glVertex3f(b, -h,  d);
        glVertex3f(b, -h, -d);
        glVertex3f(t,  h, -d);
        glVertex3f(t,  h,  d);
        
        // baixo
        glVertex3f(-b, -h, -d);
        glVertex3f( b, -h, -d);
        glVertex3f( b, -h,  d);
        glVertex3f(-b, -h,  d);

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

	// Draw something  
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);  

	// white
	glColor3f(1.0f, 1.0f, 1.0f);  

	// Main Body
	glPushMatrix();
		glTranslatef(0.0f, 0.5f, 0.0f);
		gluSphere(pObj, 0.50f, 26, 13);
	glPopMatrix();

	// Head
	glPushMatrix(); // save transform matrix state
		glTranslatef(0.0f, 1.1f, 0.0f);
		gluSphere(pObj, 0.24f, 26, 13);
	glPopMatrix(); // restore transform matrix state

	// Nose (orange)
	glColor3f(1.0f, 0.4f, 0.51f);  
	glPushMatrix();
		glTranslatef(0.0f, 1.1f, 0.2f);
		gluCylinder(pObj, 0.05f, 0.0f, 0.2f, 26, 13);  
	glPopMatrix();  

	// Eyes (black)
    glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
		glTranslatef(0.09f, 1.18f, 0.2f);
		gluSphere(pObj, 0.04f, 26, 13);
	glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
		glTranslatef(-0.09f, 1.18f, 0.2f);
		gluSphere(pObj, 0.04f, 26, 13);
	glPopMatrix();

	// Hat
	glPushMatrix();
		glTranslatef(0.0f, 1.5f, 0.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.20f, 0.18f, 0.24f, 26, 13);
	glPopMatrix();  

	// Hat brim
	glPushMatrix();
		glTranslatef(0.0f, 1.28f, 0.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.30f, 0.28f, 0.04f, 26, 13);
	glPopMatrix();

    // Scarf (red)
    glColor3f(0.0f, 0.0f, 1.0f);
	glPushMatrix();
		glTranslatef(0.0f, 1.02f, 0.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.25f, 0.28f, 0.09f, 26, 13);
	glPopMatrix();  

    glColor3f(0.1f, 0.1f, 1.0f);
    glPushMatrix();
        glTranslatef(-0.3f, .88f, 0.2f);
        glRotatef(40.0f, -2.0f, 0.0f, -4.0f);
        drawScarfTie(0.04f, 0.2f, 0.4f, 0.05f);
    glPopMatrix();


    // Buttons (black)
    // upper btn
    glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
		glTranslatef(0.0f, 0.75f, 0.43f);
		gluSphere(pObj, 0.04f, 26, 13);
	glPopMatrix();

    // middle btn
    glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
		glTranslatef(0.0f, 0.55f, 0.5f);
		gluSphere(pObj, 0.04f, 26, 13);
	glPopMatrix();

    // lower btn
    glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
		glTranslatef(0.0f, 0.35f, 0.48f);
		gluSphere(pObj, 0.04f, 26, 13);
	glPopMatrix();

    // Arms (black)
	glColor3f(0.0f, 0.0f, 0.0f);  
	glPushMatrix();
		glTranslatef(0.4f, 0.75f, 0.0f);
        glRotatef(90.0f, 0.65f, 1.0f, 0.25f);
		gluCylinder(pObj, 0.03f, 0.0f, 0.6f, 26, 13);  
	glPopMatrix();  

	glColor3f(0.0f, 0.0f, 0.0f);  
	glPushMatrix();
		glTranslatef(-0.4f, 0.75f, 0.0f);
        glRotatef(90.0f, -0.65f, -1.0f, 0.25f);
		gluCylinder(pObj, 0.03f, 0.0f, 0.6f, 26, 13);  
	glPopMatrix();  

    // hands (black)
	glColor3f(0.0f, 0.0f, 0.0f);  
	glPushMatrix();
		glTranslatef(-0.6f, 0.83f, 0.0f);
        glRotatef(90.0f, -0.95f, -1.0f, 0.0f);
		gluCylinder(pObj, 0.02f, 0.0f, 0.25f, 26, 13);  
	glPopMatrix();
    
	glColor3f(0.0f, 0.0f, 0.0f);  
	glPushMatrix();
		glTranslatef(-0.6f, 0.83f, 0.0f);
        glRotatef(90.0f, 0.5f, -1.0f, 0.0f);
		gluCylinder(pObj, 0.02f, 0.0f, 0.25f, 26, 13);  
	glPopMatrix();  
    
	glColor3f(0.0f, 0.0f, 0.0f);  
	glPushMatrix();
		glTranslatef(0.6f, 0.67f, 0.0f);
        glRotatef(90.0f, -0.65f, 1.0f, 0.0f);
		gluCylinder(pObj, 0.02f, 0.0f, 0.25f, 26, 13);  
	glPopMatrix();  

	glColor3f(0.0f, 0.0f, 0.0f);  
	glPushMatrix();
		glTranslatef(0.65f, 0.65f, 0.0f);
        glRotatef(90.0f, 0.95f, 1.0f, 0.0f);
		gluCylinder(pObj, 0.012f, 0.0f, 0.25f, 26, 13);  
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