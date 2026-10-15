#include "input.hpp"
#include "camera/camera.hpp"
#include <graphics/gl.hpp>

void cameraControls(GLFWwindow* window, Camera& camera) {
    auto down = [&](int key) { return glfwGetKey(window, key) == GLFW_PRESS; };

    float forward = float(down(GLFW_KEY_W))     - float(down(GLFW_KEY_S));
    float right   = float(down(GLFW_KEY_D))     - float(down(GLFW_KEY_A));
    float up      = float(down(GLFW_KEY_SPACE)) - float(down(GLFW_KEY_LEFT_SHIFT));

    camera.move(forward, right, up);
}