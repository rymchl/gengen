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
    texture_index(0){

    std::vector<std::string> tex_paths{
        "models/eggy/eggy_idle_0.png",  //0
        "models/eggy/eggy_idle_1.png",  //1
        "models/eggy/eggy_idle_2.png",  //2
        "models/eggy/eggy_idle_3.png",  //3

        "models/eggy/eggy_left_0.png",  //4
        "models/eggy/eggy_left_1.png",  //5
        "models/eggy/eggy_left_2.png",  //6 
        "models/eggy/eggy_left_3.png",  //7
        "models/eggy/eggy_left_4.png",  //8
        "models/eggy/eggy_left_5.png",  //9
        "models/eggy/eggy_left_6.png",  //10
        "models/eggy/eggy_left_7.png",  //11
        "models/eggy/eggy_left_8.png",  //12

        "models/eggy/eggy_right_0.png", //13
        "models/eggy/eggy_right_1.png", //14
        "models/eggy/eggy_right_2.png", //15
        "models/eggy/eggy_right_3.png", //16
        "models/eggy/eggy_right_4.png", //17
        "models/eggy/eggy_right_5.png", //18
        "models/eggy/eggy_right_6.png", //19
        "models/eggy/eggy_right_7.png", //20
        "models/eggy/eggy_right_8.png"  //21
    };

    AnimationData idleAD  = {0,3, 0.2f};
    AnimationData leftAD  = {4,12, 0.05f};
    AnimationData rightAD = {13,21, 0.05f};

    animation_query[PlayerMovement::PLAYER_IDLE] = idleAD;
    animation_query[PlayerMovement::PLAYER_LEFT] = leftAD;
    animation_query[PlayerMovement::PLAYER_RIGHT] = rightAD;
    
    //This could be sped up
    Model templateModel("models/eggy/eggy_template.obj");
    
    mesh = Mesh(templateModel.meshes[0].vertices,templateModel.meshes[0].indices,tex_paths);
}

void Player::move(glm::vec2 dp){
    position = position + dp;
}

void Player::ProcessKeyboard(PlayerMovement direction, float deltaTime){
    if(current_movement != direction){
        texture_index = animation_query[direction].index_min;
        animation_timer = 0;
    }

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
    
    mesh.active_texture = texture_index;

    mesh.draw(shader);
}

void Player::animate(float deltaTime){
    animation_timer += deltaTime;

    bool inMvmnt = (current_movement == PlayerMovement::PLAYER_LEFT || current_movement == PlayerMovement::PLAYER_RIGHT);
    AnimationData ad = animation_query[current_movement];

    if(animation_timer > ad.period){
        texture_index++;
        if(texture_index > ad.index_max) 
            texture_index = ad.index_min;
        animation_timer = 0;
    }

}

void Player::handle_collisions(std::vector<Mesh*> terrain){

    bool collision = false;

    //Add offset to player mesh (innificient to make whole new mesh instead of just the positions+offset)    
    
    Mesh player_mesh = mesh;
    for(Vertex &v : player_mesh.vertices){
        v.Position.x += position.x;
        v.Position.y += position.y;
    }

    //Future when more meshes check for groundplane to handle seperately
    for(Mesh* terrain_mesh : terrain){
        if(player_mesh.check_collision(terrain_mesh)){

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

    if(position != prev_position)
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