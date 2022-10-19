#ifndef PLAYER
#define PLAYER

#include<iostream>
#include<Model.h>
#include<unordered_map>

enum PlayerMovement{
    PLAYER_LEFT = 0,
    PLAYER_RIGHT,
    PLAYER_UP,
    PLAYER_DOWN,
    PLAYER_IDLE
};

class Player{

    public:
        glm::vec2 position;
        glm::vec2 map_offset;
        glm::vec2 velocity;

        PlayerMovement current_movement = PlayerMovement::PLAYER_IDLE;

        bool grounded;
        float mass;

        
        float animation_timer;

        Player();

        void move(glm::vec2 dp);

        void ProcessKeyboard(PlayerMovement direction, float deltaTime);
        
        void draw(Shader& shader);
        
        void animate(float deltaTime);

        void apply_force(float x, float y);
        void apply_force(glm::vec2 f) {apply_force(f.x,f.y);}

        void handle_physics(float dT, std::vector<Mesh*> collision_meshes);
        void handle_collisions(std::vector<Mesh*> terrain);

        void print();

    private:
        Mesh mesh;
        glm::vec2 prev_position;
        glm::vec2 fNet;

        struct AnimationData{
            unsigned int index_min;
            unsigned int index_max;
            float period;
        };

        std::unordered_map<PlayerMovement,AnimationData> animation_query;
        unsigned int texture_index;
        

};

#endif