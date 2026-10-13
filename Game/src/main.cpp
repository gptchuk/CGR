#include <graphics/gl.hpp>
#include <iostream>

#include "windowSettings.hpp"
#include "camera/camera.hpp"
#include "scene/scene.hpp"
#include "input/input.hpp"

Camera camera;

float lastX = 400.0f;
float lastY = 300.0f;
bool firstMouse = true;

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {

    if (firstMouse) {
        lastX = static_cast<float>(xpos);
        lastY = static_cast<float>(ypos);
        firstMouse = false;
    }

    float dx = static_cast<float>(xpos) - lastX;
    float dy = lastY - static_cast<float>(ypos);

    lastX = static_cast<float>(xpos);
    lastY = static_cast<float>(ypos);

    camera.Yaw += dx * camera.Sensitivity;
    camera.Pitch += dy * camera.Sensitivity;

    if (camera.Pitch > 89.0f)
        camera.Pitch = 89.0f;

    if (camera.Pitch < -89.0f)
        camera.Pitch = -89.0f;
}
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)  {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, mouseCallback);
    }
}
void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetCursorPosCallback(window, NULL);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstMouse = true;
    }
    cameraControls(window, camera);
}
int main() {
    if (!glfwInit()) {
        std::cerr << "Erro ao iniciar GLFW\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_LABEL, nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // vsync

    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    glEnable(GL_DEPTH_TEST);
    
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        camera.update();
        processInput(window);

        // ----------------------
        if(!beginFrame(window, camera)) {
            glfwWaitEvents();
            continue;
        }
        // ------------------------

        drawGrid();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}