#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "graphics/gl.hpp"

#include "Collider/Collider.hpp"
#include "Render/Render.hpp"

#include <vector>

class Object
{
    private:
        float
            x, y, z // position
            ;
        std::vector<Collider_Box> colision;
    public:
        void setPosition(float a, float b, float c) {
            x = a;
            y = b;
            z = c;
        }
        void addColisionBox(Collider_Box a) {
            colision.push_back(a);
        }
};

void drawObjects(GLFWwindow* window);

#endif