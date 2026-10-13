#include "camera.hpp"
#include <GLFW/glfw3.h>
#include <GL/glu.h>

bool beginFrame(GLFWwindow* window, Camera& camera) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    if (height == 0 || width == 0) return false;

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera.perspective(width, height);
    camera.lookAt();
    return true;
}
