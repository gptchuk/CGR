#define GLFW_INCLUDE_NONE
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define WINDOW_LABEL "Robot"

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

/* Here goes our drawing code */
void drawGLScene(GLFWwindow* window)
{
    GLUquadricObj *pObj;    // Quadric Object  
      
    // Clear the window with current clearing color  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  
    // Save the matrix state and do the rotations  
    glPushMatrix();

	// Move object back and do in place rotation  
	glTranslatef(0.0f, -2.0f, -10.0f);  
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);  

	// Draw something  
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);  

	// white
	glColor3f(1.0f, 1.0f, 1.0f);  

    // main body
	glPushMatrix();
		glTranslatef(0.0f, 3.4f, 0.0f);
		gluSphere(pObj, 1.1f, 26, 13);
	glPopMatrix();

    // shouders
	glPushMatrix();
		glTranslatef(0.9f, 3.5f, 0.0f);
		gluSphere(pObj, 0.7f, 26, 13);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.9f, 3.5f, 0.0f);
		gluSphere(pObj, 0.7f, 26, 13);
	glPopMatrix();

    // midhip
	glPushMatrix();
		glTranslatef(0.0f, 1.5f, 0.0f);
		gluSphere(pObj, 0.7f, 26, 13);
	glPopMatrix();
          
    //left hip
	glPushMatrix();
		glTranslatef(-0.5f, 1.2f, 0.0f);
		gluSphere(pObj, 0.5f, 26, 13);
	glPopMatrix();

    //right hip
	glPushMatrix();
		glTranslatef(0.5f, 1.2f, 0.0f);
		gluSphere(pObj, 0.5f, 26, 13);
	glPopMatrix();

    //left leg
	glColor3f(0.3f, 0.3f, 0.3f);  
	glPushMatrix();
		glTranslatef(-0.5f, 1.0f, 0.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.20f, 0.20f, 1.6f, 26, 13);
	glPopMatrix();

    //right leg
	glPushMatrix();
		glTranslatef(0.5f, 1.0f, 0.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.20f, 0.20f, 1.6f, 26, 13);
	glPopMatrix();

    //left feet
	glColor3f(1.0f, 1.0f, 1.0f);  
	glPushMatrix();
		glTranslatef(-0.5f, -0.5f, 0.0f);
        glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.30f, 0.30f, 0.6f, 26, 13);
	glPopMatrix();

    glPushMatrix();
		glTranslatef(-0.5f, -0.6f, 0.6f);
		gluSphere(pObj, 0.3f, 26, 13);
	glPopMatrix();

    glPushMatrix();
		glTranslatef(-0.5f, -0.5f, 0.0f);
		gluSphere(pObj, 0.3f, 26, 13);
	glPopMatrix();

    //left knee
	glPushMatrix();
		glTranslatef(-0.5f, 0.3f, 0.0f);
		gluSphere(pObj, 0.3f, 26, 13);
	glPopMatrix();

    //right feet
	glColor3f(1.0f, 1.0f, 1.0f);  
	glPushMatrix();
		glTranslatef(0.5f, -0.5f, 0.0f);
        glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.30f, 0.30f, 0.6f, 26, 13);
	glPopMatrix();

    glPushMatrix();
		glTranslatef(0.5f, -0.6f, 0.6f);
		gluSphere(pObj, 0.3f, 26, 13);
	glPopMatrix();

    glPushMatrix();
		glTranslatef(0.5f, -0.5f, 0.0f);
		gluSphere(pObj, 0.3f, 26, 13);
	glPopMatrix();

    //right knee
	glPushMatrix();
		glTranslatef(0.5f, 0.3f, 0.0f);
		gluSphere(pObj, 0.3f, 26, 13);
	glPopMatrix();

    //left arm
    glColor3f(0.3f, 0.3f, 0.3f);  
	glPushMatrix();
		glTranslatef(-1.2f, 3.2f, 0.0f);
        glRotatef(45.0f, 1.0f, -1.0f, 0.0f);
        gluCylinder(pObj, 0.30f, 0.30f, 1.5f, 26, 13);
	glPopMatrix();

    //left hand
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
	    glTranslatef(-1.9f, 2.5f, 1.0f);
		gluSphere(pObj, 0.40f, 26, 13);
	glPopMatrix();
    
    //left fingers
	glPushMatrix();
		glTranslatef(-1.9f, 3.1f, 1.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.10f, 0.10f, 0.5f, 26, 13);
	glPopMatrix();

    glPushMatrix();
	    glTranslatef(-1.9f, 3.1f, 1.0f);
		gluSphere(pObj, 0.1f, 26, 13);
	glPopMatrix();

    glPushMatrix();
		glTranslatef(-1.9f, 2.6f, 1.2f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        gluCylinder(pObj, 0.10f, 0.10f, 0.5f, 26, 13);
	glPopMatrix();    
    
    glPushMatrix();
		glTranslatef(-1.9f, 2.5f, 1.2f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        gluCylinder(pObj, 0.10f, 0.10f, 0.5f, 26, 13);
	glPopMatrix();

    glPushMatrix();
		glTranslatef(-1.9f, 2.4f, 1.2f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        gluCylinder(pObj, 0.10f, 0.10f, 0.5f, 26, 13);
	glPopMatrix();

    glPushMatrix();
		glTranslatef(-1.9f, 2.3f, 1.2f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        gluCylinder(pObj, 0.10f, 0.10f, 0.5f, 26, 13);
	glPopMatrix();

    glPushMatrix();
	    glTranslatef(-1.4f, 2.3f, 1.2f);
		gluSphere(pObj, 0.1f, 26, 13);
	glPopMatrix();

    glPushMatrix();
	    glTranslatef(-1.4f, 2.4f, 1.2f);
		gluSphere(pObj, 0.1f, 26, 13);
	glPopMatrix();

    glPushMatrix();
	    glTranslatef(-1.4f, 2.5f, 1.2f);
		gluSphere(pObj, 0.1f, 26, 13);
	glPopMatrix();

    glPushMatrix();
	    glTranslatef(-1.4f, 2.6f, 1.2f);
		gluSphere(pObj, 0.1f, 26, 13);
	glPopMatrix();

    glPushMatrix();
	    glTranslatef(1.9f, 2.5f, 1.0f);
		gluSphere(pObj, 0.40f, 26, 13);
	glPopMatrix();
    
    //right fingers
	glPushMatrix();
		glTranslatef(1.9f, 3.1f, 1.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.10f, 0.10f, 0.5f, 26, 13);
	glPopMatrix();

    glPushMatrix();
	    glTranslatef(1.9f, 3.1f, 1.0f);
		gluSphere(pObj, 0.1f, 26, 13);
	glPopMatrix();

    glPushMatrix();
		glTranslatef(1.9f, 2.6f, 1.2f);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        gluCylinder(pObj, 0.10f, 0.10f, 0.5f, 26, 13);
	glPopMatrix();    
    
    glPushMatrix();
		glTranslatef(1.9f, 2.5f, 1.2f);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        gluCylinder(pObj, 0.10f, 0.10f, 0.5f, 26, 13);
	glPopMatrix();

    glPushMatrix();
		glTranslatef(1.9f, 2.4f, 1.2f);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        gluCylinder(pObj, 0.10f, 0.10f, 0.5f, 26, 13);
	glPopMatrix();

    glPushMatrix();
		glTranslatef(1.9f, 2.3f, 1.2f);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        gluCylinder(pObj, 0.10f, 0.10f, 0.5f, 26, 13);
	glPopMatrix();

    glPushMatrix();
	    glTranslatef(1.4f, 2.3f, 1.2f);
		gluSphere(pObj, 0.1f, 26, 13);
	glPopMatrix();

    glPushMatrix();
	    glTranslatef(1.4f, 2.4f, 1.2f);
		gluSphere(pObj, 0.1f, 26, 13);
	glPopMatrix();

    glPushMatrix();
	    glTranslatef(1.4f, 2.5f, 1.2f);
		gluSphere(pObj, 0.1f, 26, 13);
	glPopMatrix();

    glPushMatrix();
	    glTranslatef(1.4f, 2.6f, 1.2f);
		gluSphere(pObj, 0.1f, 26, 13);
	glPopMatrix();

    //right arm
    glColor3f(0.3f, 0.3f, 0.3f);  
	glPushMatrix();
		glTranslatef(1.2f, 3.2f, 0.0f);
        glRotatef(45.0f, 1.0f, 1.0f, 0.0f);
        gluCylinder(pObj, 0.30f, 0.30f, 1.5f, 26, 13);
	glPopMatrix();

    // dark gray
	glColor3f(0.3f, 0.3f, 0.3f);
    
	glPushMatrix();
		glTranslatef(0.0f, 2.4f, 0.0f);
		gluSphere(pObj, 0.5f, 26, 13);
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
