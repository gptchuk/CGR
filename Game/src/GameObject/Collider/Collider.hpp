#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "graphics/gl.hpp"


class Collider {

};

class Collider_Box : public Collider {
    private:
        float
            minX, minY, minZ, maxX, maxY, maxZ;
    public:
        Collider_Box(float minx, float miny, float minz, float maxx, float maxy, float maxz) {
            minX = minx;
            minY = miny;
            minZ = minz;
            maxX = maxx;
            maxY = maxy;
            maxZ = maxz;
        }
        void drawCollider(float r, float g, float b) {
            
            glColor3f(r, g, b);
            glBegin(GL_LINES);

                // Bottom Face (Y = minY)
                glVertex3f(minX, minY, minZ);
                glVertex3f(maxX, minY, minZ);

                glVertex3f(maxX, minY, minZ);
                glVertex3f(maxX, minY, maxZ);

                glVertex3f(maxX, minY, maxZ);
                glVertex3f(minX, minY, maxZ);

                glVertex3f(minX, minY, maxZ);
                glVertex3f(minX, minY, minZ);

                // Top Face (Y = maxY)
                glVertex3f(minX, maxY, minZ);
                glVertex3f(maxX, maxY, minZ);

                glVertex3f(maxX, maxY, minZ);
                glVertex3f(maxX, maxY, maxZ);

                glVertex3f(maxX, maxY, maxZ);
                glVertex3f(minX, maxY, maxZ);

                glVertex3f(minX, maxY, maxZ);
                glVertex3f(minX, maxY, minZ);

                // Vertical Edges
                glVertex3f(minX, minY, minZ);
                glVertex3f(minX, maxY, minZ);

                glVertex3f(maxX, minY, minZ);
                glVertex3f(maxX, maxY, minZ);

                glVertex3f(maxX, minY, maxZ);
                glVertex3f(maxX, maxY, maxZ);

                glVertex3f(minX, minY, maxZ);
                glVertex3f(minX, maxY, maxZ);

            glEnd();
        }
};

class Collider_Cylinder : public Collider {

};
#endif