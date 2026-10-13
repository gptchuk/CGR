#include "input.hpp"
#include "camera/camera.hpp"
#include <graphics/gl.hpp>

void cameraControls(GLFWwindow* window, Camera& camera) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.cameraMovement_FORWARD();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.cameraMovement_BACKWARD();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.cameraMovement_RIGHT();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.cameraMovement_LEFT();
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) camera.cameraMovement_UPWARD();
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) camera.cameraMovement_DOWNWARD();
}