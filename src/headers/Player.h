#ifndef PLAYER
#define PLAYER

#include<iostream>
#include<Model.h>

enum PlayerMovement{
    PLAYER_LEFT = 0,
    PLAYER_RIGHT,
    PLAYER_UP,
    PLAYER_DOWN
};

class Player{

    public:
        glm::vec2 position;
        glm::vec2 map_offset;

        float rotation;
        bool lookingRight;

        Player(std::string model_path) : model(model_path), position(0,0), rotation(0), map_offset(0,0) {}  

        void rotate(float dr);
        void move(glm::vec2 dp);

        void ProcessKeyboard(PlayerMovement direction, float deltaTime);
        
        void draw(Shader& shader);
        
    private:
        Model model;
        

};

#endif