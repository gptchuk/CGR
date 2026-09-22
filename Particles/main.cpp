#define GLFW_INCLUDE_NONE
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <unistd.h>

#define WINDOW_LABEL "Particles"

void processInput(GLFWwindow *window);

// settings
static float SCREEN_WIDTH = 600;
static float SCREEN_HEIGHT = 600;

/* for the particles */
#define NUM_PARTICLES 3000
#define GRAVITY 0.0003

static int fireworkDelay = 0;

#define WIND_MAX 0.5f
#define WIND_MIN -0.5f
static float wind = 0.01f;

struct s_pf {
  float x, y, veloc_x, veloc_y;
  unsigned lifetime;
};

struct s_pf rainParticles[NUM_PARTICLES];
struct s_pf fireworkParticles[NUM_PARTICLES];


/* function to reset our viewport after a window resize */
void resizeWindow(GLFWwindow* window, int w, int h )
{
    GLfloat fAspect;  
  
    // Prevent a divide by zero  
    if(h == 0) h = 1;  

    // Set Viewport to window dimensions  
    glViewport(0, 0, w, h);  
  
    fAspect = (GLfloat)w/(GLfloat)h;
    SCREEN_WIDTH = w;
    SCREEN_HEIGHT = h;
  
    // Reset coordinate system  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
  
    // Produce the perspective projection  
    gluPerspective(35.0f, fAspect, 1.0, 40.0);  
  
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity(); 

    // Move particles 6.0 units into the screen
    glTranslatef(0.0f,0.0f,-6.0f);
}

/* function to handle key press events */
void handleKeyPress(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) 
        if(wind >= WIND_MIN) wind -= 0.001f;
  
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)  
        if(wind <= WIND_MAX) wind += 0.001f;

}
// Initialize the firework
void InitFirework()
{
    int i;
    float start_point_x = (float)(rand() % 100)/100.0;
    float start_point_y = (float)(rand() % 100)/100.0;

    for(i=0;i<NUM_PARTICLES;i++) {
        float velocity = (float)(rand() % 100)/5000.0;
        int angle = rand() % 360;
        fireworkParticles[i].veloc_x = cos( (M_PI * angle/180.0) ) * velocity;
        fireworkParticles[i].veloc_y = sin( (M_PI * angle/180.0) ) * velocity;
        fireworkParticles[i].x = start_point_x;
        fireworkParticles[i].y = start_point_y;
        fireworkParticles[i].lifetime = rand() % 100;
    }
}

void fireworks(GLFWwindow* window)
{
    int i, active_particles=0;
    /* Draw points of the firework */
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POINTS);
    for(i=0;i<NUM_PARTICLES;i++) {
        if(fireworkParticles[i].lifetime) {
            active_particles++;
            fireworkParticles[i].veloc_y -= GRAVITY;
            fireworkParticles[i].x += fireworkParticles[i].veloc_x;
            fireworkParticles[i].y += fireworkParticles[i].veloc_y;
            fireworkParticles[i].lifetime--;

            glVertex3f( fireworkParticles[i].x, fireworkParticles[i].y, 0.0f); // draw pixel
        }
    }
    glEnd();

    // if no active firework particles, wait some frames before restart
    if(!active_particles) {
        if(fireworkDelay <= 0) {
            InitFirework();
            fireworkDelay = 30 + rand() % 30; // ~ 0.5s to 1.0s at 60fps
        } else {
            fireworkDelay--;
        }
    }
}

// create/resets a sigle raindrop with the current wind
void SpawnRainDrop(int i)
{
    rainParticles[i].x = ((float)(rand() % 400) / 100.0f) - 2.0f;
    rainParticles[i].y = 2.0f + ((float)(rand() % 200) / 100.0f);

    // wind + random variance
    rainParticles[i].veloc_x = wind + (((float)(rand() % 20) / 1000.0f) - 0.01f);
    rainParticles[i].veloc_y = -(0.01f + (float)(rand() % 50) / 5000.0f);

    rainParticles[i].lifetime = 1;
}

// Initialize the rain particles
void InitRain()
{
    int i;
    for (i = 0; i < NUM_PARTICLES; i++) {
        SpawnRainDrop(i);
    }
}

void rain(GLFWwindow* window)
{
    int i;

    /* Draw points of the rain */
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    for(i=0;i<NUM_PARTICLES;i++) {
        // Updates the drop's position
        rainParticles[i].veloc_y -= GRAVITY; // aslight acceleration (optional)
        rainParticles[i].x += rainParticles[i].veloc_x;
        rainParticles[i].y += rainParticles[i].veloc_y;

        // If the drop has gone off the screen, reset it
        if(rainParticles[i].y < -2.0f || rainParticles[i].x < -3.0f || rainParticles[i].x > 3.0f) {
            SpawnRainDrop(i);
        }

        glVertex3f( rainParticles[i].x, rainParticles[i].y, 0.0f); // draws the drop's pixel
    }
    glEnd();
}


/* Here goes our drawing code */
void drawGLScene(GLFWwindow* window)
{
    /* Clear The Screen And The Depth Buffer */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    rain(window);
    fireworks(window);
    // pauses render loop for 0.0001s 
    usleep(100);

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
    
    InitFirework(); // first firework
    InitRain(); // first rain particles

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    resizeWindow(window, SCREEN_WIDTH, SCREEN_HEIGHT);

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
