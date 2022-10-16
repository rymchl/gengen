#include <Player.h>

Player::Player() : position(0,0), map_offset(0,0) {

    std::vector<Model> left_models   = {};
    std::vector<Model> right_models  = {};
    std::vector<Model> jump_models   = {};
    std::vector<Model> idle_models   = {};
    std::vector<Model> crouch_models = {};

    left_models.push_back(Model("models/eggy/eggy_left0.obj"));

    right_models.push_back(Model("models/eggy/eggy_right0.obj"));
    
    idle_models.push_back(Model("models/eggy/eggy_idle0.obj"));

    models = {
        left_models,
        right_models,
        jump_models,
        crouch_models,
        idle_models
    };

}

void Player::move(glm::vec2 dp){
    position = position + dp;
}

void Player::ProcessKeyboard(PlayerMovement direction, float deltaTime){
    current_movement = direction;
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

        case PlayerMovement::PLAYER_UP:
            return;
        case PlayerMovement::PLAYER_DOWN:
            return;
        case PlayerMovement::PLAYER_IDLE:
            return;
    };
}

void Player::draw(Shader& shader){
    shader.setVec2("uv_scale",glm::vec2(1,1));
    shader.setVec2("uv_offset",glm::vec2(0,0));
    
    shader.setVec2("vertex_offset",position);
    
    models[current_movement][model_frame].draw(shader);
}