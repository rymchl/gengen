#ifndef PLAYER
#define PLAYER

#include<iostream>
#include<Model.h>

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

        PlayerMovement current_movement = PlayerMovement::PLAYER_IDLE;
        unsigned int model_frame = 0;


        Player();

        void rotate(float dr);
        void move(glm::vec2 dp);

        void ProcessKeyboard(PlayerMovement direction, float deltaTime);
        
        void draw(Shader& shader);
        
    private:
        std::vector< std::vector<Model> > models;

       
        

};

#endif