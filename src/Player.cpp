#include <Player.h>

void Player::rotate(float dr){
    rotation = rotation + dr;
}

void Player::move(glm::vec2 dp){
    position = position + dp;
}

void Player::ProcessKeyboard(PlayerMovement direction, float deltaTime){
    std::cout << position.x << std::endl;
    switch(direction){
        case PlayerMovement::PLAYER_LEFT:
            
            if(position.x > -0.5f){
                move(glm::vec2(-1,0)*deltaTime);
                if(position.x < -0.5f){
                    map_offset.x += position.x + 0.5f;
                    position.x = -0.5f;
                }
            }
            else map_offset += glm::vec2(-1,0)*deltaTime;
            lookingRight = false;
            return;

        case PlayerMovement::PLAYER_RIGHT:

            if(position.x < 0.5f){
                move(glm::vec2(1,0)*deltaTime);
                if(position.x > 0.5f){
                    map_offset.x += position.x + -0.5f;
                    position.x = 0.5f;
                }
            }
            else map_offset += glm::vec2(1,0)*deltaTime;
            lookingRight = true;

        case PlayerMovement::PLAYER_UP:
            return;
        case PlayerMovement::PLAYER_DOWN:
            return;
    };
}

void Player::draw(Shader& shader){
    model.draw(shader);
}