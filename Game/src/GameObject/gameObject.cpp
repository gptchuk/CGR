#include "gameObject.hpp"

void drawObjects(GLFWwindow* window) {
    Collider_Box a(-1, -1, -1, 1, 1, 1);
    Object o;
    o.addColisionBox(a);
    o.setPosition(0, 1, 0);
    a.drawCollider(1, 0, 0);
}