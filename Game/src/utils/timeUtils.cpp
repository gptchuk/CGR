#include "timeUtils.hpp"
#include "graphics/gl.hpp"
#include <cmath>

float dt;
double
    previousTime  = 0.1f,
    currentTime;

float deltaTime(double t) {
    currentTime = t;
    dt = std::min(static_cast<float>(currentTime - previousTime), 0.1f);
    previousTime = currentTime;
    return dt;
}