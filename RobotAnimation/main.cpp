#define GLFW_INCLUDE_NONE
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#define WINDOW_LABEL "Robot"

void processInput(GLFWwindow *window);

// settings
#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 600

// walk
static bool walk = true;

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

void rightArm(GLFWwindow* window, GLUquadricObj *pObj, float time)
{
    const float velocity = 8.0f;
    const float amplitude  = 20.0f;
    const float elevation   = -35.0f;

    GLfloat angle = elevation + amplitude * sinf(time * velocity);

    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        glPushMatrix();
            // Origin
            glTranslatef(0.9f, 3.5f, 0.0f);
            glRotatef(angle, 0.0f, 0.0f, 1.0f);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

            // shoulder
            glColor3f(1.0f, 1.0f, 1.0f);
            gluSphere(pObj, 0.7f, 26, 13);

            // arm
            glColor3f(0.3f, 0.3f, 0.3f);
            gluCylinder(pObj, 0.30f, 0.30f, 1.5f, 26, 13);

            // hand
            glColor3f(1.0f, 1.0f, 1.0f);
            glPushMatrix();
                glTranslatef(0.0f, 0.0f, 1.8f);
                gluSphere(pObj, 0.40f, 26, 13);
            glPopMatrix();

            // fingers
            const float dedosX[4] = { -0.24f, -0.08f, 0.08f, 0.24f };
            for (int i = 0; i < 4; i++) {
                glPushMatrix();
                    glTranslatef(dedosX[i], 0.0f, 2.0f);
                    gluCylinder(pObj, 0.07f, 0.07f, 0.5f, 26, 13);
                    glTranslatef(0.0f, 0.0f, 0.5f);
                    gluSphere(pObj, 0.07f, 26, 13);
                glPopMatrix();
            }

            // thumb
            glPushMatrix();
                glTranslatef(-0.35f, 0.0f, 1.7f);
                glRotatef(-90.0f, 0.0f, 0.5f, 0.0f);
                gluCylinder(pObj, 0.08f, 0.08f, 0.4f, 26, 13);
                glTranslatef(0.0f, 0.0f, 0.4f);
                gluSphere(pObj, 0.08f, 26, 13);
            glPopMatrix();
        glPopMatrix();

       } else {
        glPushMatrix();
            // Origin (espelho do braço esquerdo)
            glTranslatef(0.9f, 3.5f, 0.0f);
            glRotatef(-90.0f, 1.0f, -0.5f, 0.0f);
            glRotatef(180.0f, 0.0f, -1.0f, 0.0f);
            glRotatef(45.0f, 1.0f, -1.0f, -1.0f);

            // shoulder
            glColor3f(1.0f, 1.0f, 1.0f);
            gluSphere(pObj, 0.7f, 26, 13);

            // arm
            glColor3f(0.3f, 0.3f, 0.3f);
            gluCylinder(pObj, 0.30f, 0.30f, 1.5f, 26, 13);

            // hand
            glColor3f(1.0f, 1.0f, 1.0f);
            glPushMatrix();
                glTranslatef(0.0f, 0.0f, 1.8f);
                gluSphere(pObj, 0.40f, 26, 13);
                // fingers
                const float dedosX[4] = { -0.24f, -0.08f, 0.08f, 0.24f };
                for (int i = 0; i < 4; i++) {
                    glPushMatrix();
                        glTranslatef(dedosX[i], 0.0f, 0.2f);
                        gluCylinder(pObj, 0.07f, 0.07f, 0.5f, 26, 13);
                        glTranslatef(0.0f, 0.0f, 0.5f);
                        gluSphere(pObj, 0.07f, 26, 13);
                    glPopMatrix();
                }

                // thumb (lado oposto ao do braço esquerdo)
                glPushMatrix();
                    glTranslatef(0.35f, 0.0f, 0.0f);
                    glRotatef(90.0f, 0.0f, 0.5f, 0.0f);
                    gluCylinder(pObj, 0.08f, 0.08f, 0.4f, 26, 13);
                    glTranslatef(0.0f, 0.0f, 0.4f);
                    gluSphere(pObj, 0.08f, 26, 13);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    }
}

void leftArm(GLFWwindow* window, GLUquadricObj *pObj, float time)
{
    const float velocity = 8.0f;
    const float amplitude  = 20.0f;
    const float elevation   = -35.0f;

    GLfloat angle = elevation + amplitude * sinf(time * velocity);

    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glPushMatrix();
            // Origin
            glTranslatef(-0.9f, 3.5f, 0.0f);
            glRotatef(180.0f, 0.0f, 0.0f, -1.0f);
            glRotatef(angle, 0.0f, 0.0f, -1.0f);
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

            // shoulder
            glColor3f(1.0f, 1.0f, 1.0f);
            gluSphere(pObj, 0.7f, 26, 13);

            // arm
            glColor3f(0.3f, 0.3f, 0.3f);
            gluCylinder(pObj, 0.30f, 0.30f, 1.5f, 26, 13);

            // hand
            glColor3f(1.0f, 1.0f, 1.0f);
            glPushMatrix();
                glTranslatef(0.0f, 0.0f, 1.8f);
                gluSphere(pObj, 0.40f, 26, 13);
            glPopMatrix();

            // fingers
            const float dedosX[4] = { -0.24f, -0.08f, 0.08f, 0.24f };
            for (int i = 0; i < 4; i++) {
                glPushMatrix();
                    glTranslatef(dedosX[i], 0.0f, 2.0f);
                    gluCylinder(pObj, 0.07f, 0.07f, 0.5f, 26, 13);
                    glTranslatef(0.0f, 0.0f, 0.5f);
                    gluSphere(pObj, 0.07f, 26, 13);
                glPopMatrix();
            }

            // thumb
            glPushMatrix();
                glTranslatef(-0.35f, 0.0f, 1.7f);
                glRotatef(-90.0f, 0.0f, 0.5f, 0.0f);
                gluCylinder(pObj, 0.08f, 0.08f, 0.4f, 26, 13);
                glTranslatef(0.0f, 0.0f, 0.4f);
                gluSphere(pObj, 0.08f, 26, 13);
            glPopMatrix();
        glPopMatrix();

    } else {
        glPushMatrix();
            // Origin
            glTranslatef(-0.9f, 3.5f, 0.0f);
            glRotatef(-90.0f, 1.0f, 0.5f, 0.0f);
            glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
            glRotatef(45.0f, 1.0f, 1.0f, 1.0f);

            // shoulder
            glColor3f(1.0f, 1.0f, 1.0f);
            gluSphere(pObj, 0.7f, 26, 13);

            // arm
            glColor3f(0.3f, 0.3f, 0.3f);
            gluCylinder(pObj, 0.30f, 0.30f, 1.5f, 26, 13);

            // hand
            glColor3f(1.0f, 1.0f, 1.0f);
            glPushMatrix();
                glTranslatef(0.0f, 0.0f, 1.8f);
                gluSphere(pObj, 0.40f, 26, 13);
                // fingers
                const float dedosX[4] = { -0.24f, -0.08f, 0.08f, 0.24f };
                for (int i = 0; i < 4; i++) {
                    glPushMatrix();
                        glTranslatef(dedosX[i], 0.0f, 0.2f);
                        gluCylinder(pObj, 0.07f, 0.07f, 0.5f, 26, 13);
                        glTranslatef(0.0f, 0.0f, 0.5f);
                        gluSphere(pObj, 0.07f, 26, 13);
                    glPopMatrix();
                }

                // thumb
                glPushMatrix();
                    glTranslatef(-0.35f, 0.0f, 0.0f);
                    glRotatef(-90.0f, 0.0f, 0.5f, 0.0f);
                    gluCylinder(pObj, 0.08f, 0.08f, 0.4f, 26, 13);
                    glTranslatef(0.0f, 0.0f, 0.4f);
                    gluSphere(pObj, 0.08f, 26, 13);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    }
}

static void drawLeg(GLUquadricObj *pObj, float xHip, float angle)
{
    glPushMatrix();
        glTranslatef(xHip, 1.2f, 0.0f);          // pivô = quadril
        glRotatef(angle, 1.0f, 0.0f, 0.0f);      // balanço frente/trás

        // coxa e canela
        glColor3f(0.3f, 0.3f, 0.3f);
        glPushMatrix();
            glTranslatef(0.0f, -0.2f, 0.0f);
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(pObj, 0.20f, 0.20f, 0.6f, 26, 13);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0f, -1.0f, 0.0f);
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(pObj, 0.20f, 0.20f, 0.6f, 26, 13);
        glPopMatrix();

        // joelho
        glColor3f(1.0f, 1.0f, 1.0f);
        glPushMatrix();
            glTranslatef(0.0f, -0.9f, 0.0f);
            gluSphere(pObj, 0.3f, 26, 13);
        glPopMatrix();

        // pé
        glPushMatrix();
            glTranslatef(0.0f, -1.7f, 0.0f);
            glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(pObj, 0.30f, 0.30f, 0.6f, 26, 13);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0f, -1.8f, 0.6f);
            gluSphere(pObj, 0.3f, 26, 13);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0f, -1.7f, 0.0f);
            gluSphere(pObj, 0.3f, 26, 13);
        glPopMatrix();
    glPopMatrix();
}

void legs(GLUquadricObj *pObj, float time, bool walk)
{
    float velocity;
    if (walk) velocity = 6.0f;
    else velocity = 0.0f;

    float amplitude = 25.0f;

    GLfloat swing = amplitude * sinf(time * velocity);

    drawLeg(pObj, -0.5f,  swing); 
    drawLeg(pObj,  0.5f, -swing);
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

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) walk = true;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) walk = false;
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
	glTranslatef(0.0f, -2.0f, -15.0f);  
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);  

	// Draw something  
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);  


    // head
	glColor3f(1.0f, 1.0f, 1.0f); 
	glPushMatrix();
		glTranslatef(0.0f, 4.6f, 0.1f);
		gluSphere(pObj, 0.6f, 26, 13);
	glPopMatrix();

	glColor3f(0.5f, 0.8f, 1.0f); 
	glPushMatrix();
		glTranslatef(0.0f, 4.6f, 0.25f);
		gluSphere(pObj, 0.5f, 26, 13);
	glPopMatrix();

    // eyes
	glColor3f(0.3f, 0.3f, 0.3f); 
	glPushMatrix();
		glTranslatef(-0.15f, 4.6f, 0.65f);
		gluSphere(pObj, 0.12f, 26, 13);
	glPopMatrix();
    
	glPushMatrix();
		glTranslatef(0.15f, 4.6f, 0.65f);
		gluSphere(pObj, 0.12f, 26, 13);
	glPopMatrix();

    // main body
	glColor3f(1.0f, 1.0f, 1.0f);  
	glPushMatrix();
		glTranslatef(0.0f, 3.4f, 0.0f);
		gluSphere(pObj, 1.1f, 26, 13);
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
    
    // dark gray
	glColor3f(0.3f, 0.3f, 0.3f);
    
	glPushMatrix();
		glTranslatef(0.0f, 2.4f, 0.0f);
		gluSphere(pObj, 0.5f, 26, 13);
	glPopMatrix();

    rightArm(window, pObj, (float)glfwGetTime());
    leftArm(window, pObj, (float)glfwGetTime());
    
    legs(pObj, (float)glfwGetTime(), walk);

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
