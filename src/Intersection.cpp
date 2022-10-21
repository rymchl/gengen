#include <Intersection.h>

Intersection::Intersection() : found(false) {}
Intersection::Intersection(bool found) : found(found) {}
Intersection::Intersection(glm::vec2 position) : position(position), found(true) {}
Intersection::Intersection(bool found, glm::vec2 position) : position(position), found(found) {}

void Intersection::print(){
    if(found){
        printf("<%.2f,%.2f>\n",position.x,position.y);
    }
    else printf("Intersection not found.\n");
}

