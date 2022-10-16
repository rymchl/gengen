#ifndef MAP
#define MAP

#include <Model.h>

class Map{

    public:
        Model ground;
        Model moon;
        std::vector<Model> background_layers = {};
        float time_offset;


        Map();
        void draw(Shader& shader, glm::vec2 offset);

};

#endif
