#include <Player.h>

Player::Player() :
    prev_position(0,0.01f),
    position(0,0.01f),
    velocity(0,0),
    fNet(0,0),
    map_offset(0,0),
    mass(60),
    grounded(true),
    animation_timer(0),
    model_frame(0) {

    std::vector<Model> left_models   = {};
    std::vector<Model> right_models  = {};
    std::vector<Model> jump_models   = {};
    std::vector<Model> idle_models   = {};
    std::vector<Model> crouch_models = {};

    left_models.push_back(Model("models/eggy/left_0.obj"));
    left_models.push_back(Model("models/eggy/left_1.obj"));
    left_models.push_back(Model("models/eggy/left_2.obj"));
    left_models.push_back(Model("models/eggy/left_3.obj"));
    left_models.push_back(Model("models/eggy/left_4.obj"));
    left_models.push_back(Model("models/eggy/left_5.obj"));
    left_models.push_back(Model("models/eggy/left_6.obj"));
    left_models.push_back(Model("models/eggy/left_7.obj"));
    left_models.push_back(Model("models/eggy/left_8.obj"));

    right_models.push_back(Model("models/eggy/right_0.obj"));
    right_models.push_back(Model("models/eggy/right_1.obj"));
    right_models.push_back(Model("models/eggy/right_2.obj"));
    right_models.push_back(Model("models/eggy/right_3.obj"));
    right_models.push_back(Model("models/eggy/right_4.obj"));
    right_models.push_back(Model("models/eggy/right_5.obj"));
    right_models.push_back(Model("models/eggy/right_6.obj"));
    right_models.push_back(Model("models/eggy/right_7.obj"));
    right_models.push_back(Model("models/eggy/right_8.obj"));

    idle_models.push_back(Model("models/eggy/idle_0.obj"));
    idle_models.push_back(Model("models/eggy/idle_1.obj"));
    idle_models.push_back(Model("models/eggy/idle_2.obj"));
    idle_models.push_back(Model("models/eggy/idle_3.obj"));

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
    if(current_movement != direction) model_frame = 0;

    current_movement = direction;
    
    if(direction != PlayerMovement::PLAYER_LEFT && direction != PlayerMovement::PLAYER_RIGHT && grounded) velocity.x = 0;
    switch(direction){
        case PlayerMovement::PLAYER_LEFT:
            velocity.x = -1;
            return;

        case PlayerMovement::PLAYER_RIGHT:
            velocity.x = 1;
            return;

        case PlayerMovement::PLAYER_UP:
            //if(grounded) force_queue += glm::vec2(0,1.0f) * 50.0f * mass;
            if(grounded) velocity.y += 3.5f;
            grounded = false;
            if(velocity.x < 0) current_movement = PlayerMovement::PLAYER_LEFT;
            else if(velocity.x > 0) current_movement = PlayerMovement::PLAYER_RIGHT;
            else current_movement = PlayerMovement::PLAYER_IDLE;
            return;
        case PlayerMovement::PLAYER_DOWN:
            //move(glm::vec2(0,-1)*deltaTime);
            current_movement = PlayerMovement::PLAYER_IDLE;
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

#define MVMT_ANIMATION_PERIOD 0.05f
#define IDLE_ANIMATION_PERIOD 0.2f

void Player::animate(float deltaTime){
    animation_timer += deltaTime;

    bool inMvmnt = (current_movement == PlayerMovement::PLAYER_LEFT || current_movement == PlayerMovement::PLAYER_RIGHT);

    if(inMvmnt && (animation_timer > MVMT_ANIMATION_PERIOD)){
        model_frame = (model_frame + 1) % models[current_movement].size();
        animation_timer = 0;
    }

    else if((current_movement == PlayerMovement::PLAYER_IDLE) && (animation_timer > IDLE_ANIMATION_PERIOD)) {
        model_frame = (model_frame + 1) % models[current_movement].size();
        animation_timer = 0;
    }

}

void Player::handle_collisions(std::vector<Mesh*> terrain){

    bool collision = false;


    //Add offset to player mesh (innificient to make whole new mesh instead of just the positions+offset)    
    Mesh* player_mesh = new Mesh(models[current_movement][model_frame].meshes[0]);
    for(Vertex &v : player_mesh->vertices){
        v.Position.x += position.x;
        v.Position.y += position.y;
    }

    //Future when more meshes check for groundplane to handle seperately
    for(Mesh* terrain_mesh : terrain){
        if(player_mesh->check_collision(terrain_mesh)){

            position = prev_position;
            grounded = true;

            fNet = glm::vec2(0,0);
            velocity.y = 0;

        }
    }

    prev_position = position;
}



void Player::handle_physics(float dT, std::vector<Mesh*> collision_meshes){

    if(!grounded){
        velocity.y -= 9.81 * dT;
    }
    move(velocity * dT);

    if(position.x < -0.5f){
        map_offset.x += position.x + 0.5f;
        position.x = -0.5f;
    }
    
    else if(position.x > 0.5f){
        map_offset.x += position.x - 0.5f;
        position.x = 0.5f;
    }

    handle_collisions(collision_meshes);
}

void Player::apply_force(float x, float y){
    fNet.x += x;
    fNet.y += y;
}

void Player::print(){
    printf("|----------------------------------------|\n");
    printf("|FNet     :  <%+2.8f,%+2.8f> |\n",fNet.x,fNet.y);
    printf("|Velocity :  <%+2.8f,%+2.8f> |\n",velocity.x,velocity.y);
    printf("|Position :  <%+2.8f,%+2.8f> |\n",position.x,position.y);
    printf("|---------------------------S-------------|\n");
}