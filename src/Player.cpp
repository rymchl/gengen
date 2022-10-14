#include <Player.h>

void Player::rotate(float dr){
    rotation = rotation + dr;
}

void Player::move(glm::vec3 dp){
    position = position + dp;
}

void Player::ProcessKeyboard(PlayerMovement direction, float deltaTime){
    switch(direction){
        case PlayerMovement::PLAYER_LEFT:
            move(glm::vec4(-1,0,0,0)*deltaTime);
            return;
        case PlayerMovement::PLAYER_RIGHT:
            move(glm::vec4(1,0,0,0)*deltaTime);
            return;
        case PlayerMovement::PLAYER_UP:
            return;
        case PlayerMovement::PLAYER_DOWN:
            return;
    };
}

void Player::draw(Shader& shader){
    model.draw(shader);
}