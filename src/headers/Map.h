#ifndef MAP
#define MAP

#include <Model.h>

class Map{

    public:
        
        //Model moon;
        //std::vector<Model> background_layers = {};
        Mesh background;
        unsigned int background_tex_count;
        Model ground;
        std::vector<Mesh*> terrain_meshes;
        float time_offset;


        Map();
        void draw(Shader& shader, glm::vec2 offset);

};

#endif
