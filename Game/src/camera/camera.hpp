#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <graphics/gl.hpp>
#include <cmath>
#include <algorithm>

#include "utils/mathUtils.hpp"
#include "utils/timeUtils.hpp"

class Camera {
    private: // variables
        float
            x, y, z,    // Position
            fx, fy, fz, // Front vector
            ux, uy, uz, // Up vector
            rx, ry, rz, // Right vector
            wx, wy, wz, // World Up vector
            velocity; // delta time

    public: // variables
        float
            Yaw, Pitch, Roll, // rotations
            Fov, Speed, Sensitivity, // mods
            NearPlane, FarPlane; // min and max render limit
    

    public: // methods
        Camera() {
            x = 0.0;
            y = 2.0;
            z = 5.0;
            Fov = 70.0f;
            fx = 0, fy = 0, fz = -1;
            rx = 1, rz = 0;
            Yaw = -90.0;
            Pitch = 0.0;
            Roll = 0.0;
            Speed = 5.0;
            Sensitivity = 0.1;
            NearPlane = 0.1;
            FarPlane = 1000.0;
        }
        void update(){
            velocity = Speed * deltaTime(glfwGetTime());

            Yaw = fmodf(Yaw, 360.0f);

            float yaw = toRadians(Yaw);
            float pitch = toRadians(Pitch);
            
            fx = cosf(yaw) * cosf(pitch);
            fy = sinf(pitch);
            fz = sinf(yaw) * cosf(pitch);
            
            rx = -sinf(yaw);
            rz = cosf(yaw);
        }
        void perspective(int width, int height) {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            gluPerspective(
                Fov,
                (double) width/height,
                NearPlane,
                FarPlane

            );
        }
        void lookAt() {
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            gluLookAt(
                x, y, z,
                x + fx,
                y + fy,
                z + fz,
                0.0, 1.0, 0.0
            );
        }

    public:
        void move(float forward, float right, float up) {
            float dx = fx * forward + rx * right;
            float dy = fy * forward + up;
            float dz = fz * forward + rz * right;

            float len = std::sqrt(dx*dx + dy*dy + dz*dz);
            if (len < 1e-6f) return;          // sem input, ou W+S se cancelando

            float k = velocity / len;
            x += dx * k;
            y += dy * k;
            z += dz * k;
        }

        float getCameraFov() { return Fov; }
        void setCameraFov(float fov) { Fov = std::clamp(fov, 1.0f, 179.0f); }

};

bool beginFrame(GLFWwindow* window, Camera& camera);


#endif