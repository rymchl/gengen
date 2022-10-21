#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <glm/glm.hpp>
#include <stdio.h>

class Intersection{
    public:
        
        Intersection();
        Intersection(bool found);
        Intersection(glm::vec2 position);
        Intersection(bool found, glm::vec2 position);
        
        bool found;
        glm::vec2 position;

        void print();
};

#endif