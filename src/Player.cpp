#include <Player.h>
#include <Misc.h>

//----------------------------------------------------------------------------------------------------
//CONSTRUCTION
//----------------------------------------------------------------------------------------------------
Player::Player() :
    prev_position(0,0.01f),
    position(0,0.01f),
    velocity(0,0),
    fNet(0,0),
    map_offset(0,0),
    grounded(true),
    animation_timer(0),
    texture_index(0){

    std::vector<std::string> tex_paths{
        "models/eggy/eggy/idle/0.png",          //0
        "models/eggy/eggy/idle/1.png",          //1
        "models/eggy/eggy/idle/2.png",          //2
        "models/eggy/eggy/idle/3.png",          //3

        "models/eggy/eggy/walk/left/0.png",     //4
        "models/eggy/eggy/walk/left/1.png",     //5
        "models/eggy/eggy/walk/left/2.png",     //6 
        "models/eggy/eggy/walk/left/3.png",     //7
        "models/eggy/eggy/walk/left/4.png",     //8
        "models/eggy/eggy/walk/left/5.png",     //9
        "models/eggy/eggy/walk/left/6.png",     //10
        "models/eggy/eggy/walk/left/7.png",     //11
        "models/eggy/eggy/walk/left/8.png",     //12

        "models/eggy/eggy/walk/right/0.png",    //13
        "models/eggy/eggy/walk/right/1.png",    //14
        "models/eggy/eggy/walk/right/2.png",    //15
        "models/eggy/eggy/walk/right/3.png",    //16
        "models/eggy/eggy/walk/right/4.png",    //17
        "models/eggy/eggy/walk/right/5.png",    //18
        "models/eggy/eggy/walk/right/6.png",    //19
        "models/eggy/eggy/walk/right/7.png",    //20
        "models/eggy/eggy/walk/right/8.png",    //21

        "models/eggy/eggy/jump/normal/0.png",   //22
        "models/eggy/eggy/jump/normal/1.png",   //23
        "models/eggy/eggy/jump/normal/2.png",   //24
        "models/eggy/eggy/jump/normal/3.png",   //25

        "models/eggy/eggy/jump/left/0.png",     //26
        "models/eggy/eggy/jump/left/1.png",     //27
        "models/eggy/eggy/jump/left/2.png",     //28
        "models/eggy/eggy/jump/left/3.png",     //29

        "models/eggy/eggy/jump/right/0.png",    //30
        "models/eggy/eggy/jump/right/1.png",    //31
        "models/eggy/eggy/jump/right/2.png",    //32
        "models/eggy/eggy/jump/right/3.png",    //33

        "models/eggy/eggy/fall/normal/0.png",   //34
        "models/eggy/eggy/fall/normal/1.png",   //35
        "models/eggy/eggy/fall/normal/2.png",   //36
        "models/eggy/eggy/fall/normal/3.png",   //37
        "models/eggy/eggy/fall/normal/4.png",   //38

        "models/eggy/eggy/fall/left/0.png",     //39
        "models/eggy/eggy/fall/left/1.png",     //40
        "models/eggy/eggy/fall/left/2.png",     //41
        "models/eggy/eggy/fall/left/3.png",     //42
        "models/eggy/eggy/fall/left/4.png",     //43

        "models/eggy/eggy/fall/right/0.png",    //44
        "models/eggy/eggy/fall/right/1.png",    //45
        "models/eggy/eggy/fall/right/2.png",    //46
        "models/eggy/eggy/fall/right/3.png",    //47
        "models/eggy/eggy/fall/right/4.png"     //48
    };

    AnimationData idleAD        (00,03,CycleStyle::CYCLE_RESTART);
    AnimationData walk_leftAD   (04,12,CycleStyle::CYCLE_RESTART);
    AnimationData walk_rightAD  (13,21,CycleStyle::CYCLE_RESTART);
    AnimationData jump_normalAD (22,25,CycleStyle::CYCLE_NONE);
    AnimationData jump_leftAD   (26,29,CycleStyle::CYCLE_NONE);
    AnimationData jump_rightAD  (30,33,CycleStyle::CYCLE_NONE);
    AnimationData fall_normalAD (34,38,CycleStyle::CYCLE_REVERSE);
    AnimationData fall_leftAD   (39,43,CycleStyle::CYCLE_REVERSE);
    AnimationData fall_rightAD  (44,48,CycleStyle::CYCLE_REVERSE);
    

    animation_query[PlayerMovement::PLAYER_IDLE]        = idleAD;
    animation_query[PlayerMovement::PLAYER_WALK_LEFT]   =  walk_leftAD;
    animation_query[PlayerMovement::PLAYER_WALK_RIGHT]  = walk_rightAD;
    animation_query[PlayerMovement::PLAYER_JUMP_NORMAL] = jump_normalAD;
    animation_query[PlayerMovement::PLAYER_JUMP_LEFT]   = jump_leftAD;
    animation_query[PlayerMovement::PLAYER_JUMP_RIGHT]  = jump_rightAD;
    animation_query[PlayerMovement::PLAYER_FALL_NORMAL] = fall_normalAD;
    animation_query[PlayerMovement::PLAYER_FALL_LEFT]   = fall_leftAD;
    animation_query[PlayerMovement::PLAYER_FALL_RIGHT]  = fall_rightAD;

    //This could be sped up
    Model templateModel("models/eggy/eggy/template.obj");
    
    mesh = Mesh(templateModel.meshes[0].vertices,templateModel.meshes[0].indices,tex_paths);

    width = 2 * glm::length(getVec_centre_to_right());
}
//----------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------
//PHYSICS AND TRANSFORMATIONS
//----------------------------------------------------------------------------------------------------

void Player::step_physics(float dT, std::vector<Mesh*> collision_meshes){


    //Check if grounded if not moving upward
    grounded = false;
    if(velocity.y <= 0){
        glm::vec2 BL = getGlobalBL();
        glm::vec2 BR = getGlobalBR();
        glm::vec2 dV = BR - BL;
        const unsigned int subdivisions = 4;
        if(subdivisions > 0) dV = dV / (float)subdivisions;
        for(int i = 0; i <= subdivisions; i++){
            glm::vec2 p = BL + ((float)i * dV);
            for(Mesh* mesh : collision_meshes){
                for(Tri& tri : mesh->getTris()){
                    Intersection intersection = find_min_intersection(p,glm::vec2(0,-0.01f),tri);
                    if(intersection.found){
                        grounded = true;
                        velocity.y = 0;
                        break;
                    }
                }   
                if(grounded) break;
            }
            if(grounded) break;
        }    
    }
   

   

    if(!grounded){
        velocity.y -= 9.81 * dT;
    }


    glm::vec2 saved_velocity = velocity;

    glm::vec2 velocity_x(velocity.x,0);
    glm::vec2 velocity_y(0,velocity.y);

    velocity = velocity_x;
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

    velocity = velocity_y;
    move(velocity_y * dT);

    if(position != prev_position)
        handle_collisions(collision_meshes);

    velocity = glm::vec2(saved_velocity.x, velocity.y);
}

void Player::handle_physics(float dT, std::vector<Mesh*> collision_meshes){

    static float substep = 1.0f/60.0f;
    while(dT > substep){
        step_physics(substep,collision_meshes);
        dT -= substep;
    }
    if(dT > 0) step_physics(dT,collision_meshes);
   
}

glm::vec2 Player::get_collision_offset(Tri& tri){
    const unsigned int subdivisions = 2;

    //Cast rays from corners, and (subdivisions) line segments along mesh 

    std::vector<Intersection> Intersections;

    glm::vec2 TL = getGlobalTL();
    glm::vec2 TR = getGlobalTR();
    glm::vec2 BR = getGlobalBR();
    glm::vec2 BL = getGlobalBL();

    glm::vec2 TLtoTR = TR-TL;
    glm::vec2 BLtoBR = BR-BL;

    glm::vec2 BLtoTL = TL-BL;
    glm::vec2 BRtoTR = TR-BR;

    Intersection intersection;

    if(velocity.y > 0){
        glm::vec2 dV = TLtoTR;
        if(subdivisions > 0) dV = dV / (float)subdivisions;
        for(int i = 0; i < subdivisions + 1; i++){
            glm::vec2 p = TL + ((float)i * dV);
            intersection = find_min_intersection(p, velocity, tri);
            if(intersection.found){
                return (intersection.position - p);
            }
        }
    }

    if(velocity.y < 0){
        //CHECK BL
        //CHECK BL->BR SUBDIVISIONS 
        //CHECK BR 
        glm::vec2 dV = BLtoBR;
        if(subdivisions > 0) dV = dV / (float)subdivisions;
        for(int i = 0; i < subdivisions + 1; i++){
            glm::vec2 p = BL + ((float)i * dV);
            intersection = find_min_intersection(p, velocity, tri);
            if(intersection.found){
                return (intersection.position - p);
            }
        }
    
    }

    if(velocity.x < 0){
        //CHECK BL
        //CHECK BL->TL SUBDIVISIONS
        //CHECK TL 
        glm::vec2 dV = BLtoTL;
        if(subdivisions > 0) dV = dV / (float)subdivisions;
        for(int i = 0; i < subdivisions + 1; i++){
            glm::vec2 p = BL + ((float)i * dV);
            intersection = find_min_intersection(p, velocity, tri);
            if(intersection.found){
                return (intersection.position - p);
            }
        }
    }
    
    if(velocity.x > 0){
        //CHECK BR
        //CHECK BR->TR SUBDIVISIONS
        //CHECK TR
            glm::vec2 dV = BRtoTR;
        if(subdivisions > 0) dV = dV / (float)subdivisions;
        for(int i = 0; i < subdivisions + 1; i++){
            glm::vec2 p = BR + ((float)i * dV);
            intersection = find_min_intersection(p, velocity, tri);
            if(intersection.found){
                return (intersection.position - p);
            }
        }
    }
    return glm::vec2(0,0);
}

void Player::handle_collisions(std::vector<Mesh*> terrain){
    Mesh player_mesh = mesh;
    for(Vertex &v : player_mesh.vertices){
        v.Position.x += position.x;
        v.Position.y += position.y;
    }

    //Handle any collisions
    for(Mesh* terrain_mesh : terrain){
        Tri tri = player_mesh.check_collision(terrain_mesh);
        if(tri.a != nullptr){
            glm::vec2 best = prev_position;
            glm::vec2 pos = position;
            glm::vec2 dir = prev_position - position;

            bool prev_collision = true;

            //grounded = true;
            //velocity.y = 0;

             //binary search N times;
            int N = 4;
            while(N > 0){
                dir = dir / 2.0f;
                pos += dir;
                player_mesh = mesh;
                for(Vertex &v : player_mesh.vertices){
                    v.Position.x += pos.x;
                    v.Position.y += pos.y;
                }
                tri = player_mesh.check_collision(terrain_mesh);

                //No collision
                if(tri.a == nullptr){
                    best = pos;
                    if(prev_collision){
                        dir = - dir;
                        prev_collision = false;
                    }
                        
                }
                //Collision
                else{
                    if(!prev_collision){
                        dir = - dir;
                        prev_collision = true;
                    }
                }
                N--;
            }
            position = best;
            /*
            position = prev_position;
            glm::vec2 offset = get_collision_offset(tri);

            //If we found a suitable offset, use it
            if(offset != glm::vec2(0,0)) {
                if(offset.y < 0){
                    //move down -> hit ground
                    grounded = true;
                    velocity.y = 0;
                }
                else if(offset.y > 0){
                    //move up -> hit roof
                    velocity.y = 0;
                }
                if(offset.x < 0){
                    //move left -> hit left
                    velocity.x = 0;
                }
                else if(offset.x > 0){
                    //move right -> hit right
                    velocity.x = 0;
                }
                position += offset - 0.01f * glm::normalize(offset);
            }
            else{
                    printf("FAIL\n");
                    grounded = true;
                    velocity.y = 0;
            }
            */
        }
    }
    prev_position = position;
}


void Player::apply_force(float x, float y){
    fNet.x += x;
    fNet.y += y;
}

void Player::move(glm::vec2 dp){
    position = position + dp;
}
//----------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------
//GRAPHICS
//----------------------------------------------------------------------------------------------------
void Player::draw(Shader& shader){
    shader.setVec2("uv_scale",glm::vec2(1,1));
    shader.setVec2("uv_offset",glm::vec2(0,0));
    shader.setVec2("vertex_offset",position);
    
    mesh.active_texture = texture_index;

    mesh.draw(shader);
}

void Player::animate(float deltaTime){
    animation_timer += deltaTime;

    AnimationData* ad = &(animation_query[current_movement]);

    if(animation_timer > ad->period){
        if(!ad->reverse){
            texture_index++;
            if(texture_index > ad->index_max){
                if(ad->style == CycleStyle::CYCLE_NONE){
                    texture_index = ad->index_max;
                }
                else if(ad->style == CycleStyle::CYCLE_RESTART){
                    texture_index = ad->index_min;
                }
                else if(ad->style == CycleStyle::CYCLE_REVERSE){
                    texture_index = ad->index_max - 1;
                    ad->reverse = true;
                }
            }
        }
        else{
            //assumng ad->style == reverse
            texture_index --;
            if(texture_index < ad->index_min){
                ad->reverse = false;
                texture_index = ad->index_min + 1;
            }
        }
            
        animation_timer = 0;
    }

}
//----------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------
//INPUT PROCESSING
//----------------------------------------------------------------------------------------------------
void Player::processInput(GLFWwindow* window,float deltaTime){
    bool input = false;
        
    if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)){
        processMovement(PlayerInput::PLAYER_INPUT_JUMP, deltaTime);
        input = true;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        processMovement(PlayerInput::PLAYER_INPUT_LEFT, deltaTime);
        input = true;
    }
        
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        processMovement(PlayerInput::PLAYER_INPUT_RIGHT, deltaTime);
        input = true;
    }
        
    //if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){   
    //    input = true;
    //}

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
        position = glm::vec2(0,0);
        velocity = glm::vec2(0,0);
        processMovement(PlayerInput::PLAYER_INPUT_NONE, deltaTime);
    }

    if(!input) processMovement(PlayerInput::PLAYER_INPUT_NONE, deltaTime);
}

void Player::processMovement(PlayerInput input, float deltaTime){

    PlayerMovement previous_movement = current_movement;

    bool falling = !grounded && (velocity.y < 0);
    //In the air
    if(!grounded){
        //Falling
        if(velocity.y < 0){
            if(input == PlayerInput::PLAYER_INPUT_LEFT){
                current_movement = PlayerMovement::PLAYER_FALL_LEFT;
                velocity.x = -1;
            }
            else if(input == PlayerInput::PLAYER_INPUT_RIGHT){
                current_movement = PlayerMovement::PLAYER_FALL_RIGHT;
                velocity.x = 1;
            }
            //Handle if player starts falling without input 
            // eg hits jump and then no left/right input, or walk off cliff
            else if(input == PlayerInput::PLAYER_INPUT_NONE){
               if(velocity.x < 0)
                    current_movement = PlayerMovement::PLAYER_FALL_LEFT;

                else if(velocity.x > 0)
                    current_movement = PlayerMovement::PLAYER_FALL_RIGHT;

                else     
                    current_movement = PlayerMovement::PLAYER_FALL_NORMAL;
                
            }
        }
        //Jumping
        else if(velocity.y >= 0){
            if(input == PlayerInput::PLAYER_INPUT_LEFT){
                current_movement = PlayerMovement::PLAYER_JUMP_LEFT;
                velocity.x = -1;
            }
            else if(input == PlayerInput::PLAYER_INPUT_RIGHT){
                current_movement = PlayerMovement::PLAYER_JUMP_RIGHT;
                velocity.x = 1;
            }
        }
    }
    //On the ground
    else{
        if(input == PlayerInput::PLAYER_INPUT_LEFT){
            current_movement = PlayerMovement::PLAYER_WALK_LEFT;
            velocity.x = -1;
        }
        else if(input == PlayerInput::PLAYER_INPUT_RIGHT){
            current_movement = PlayerMovement::PLAYER_WALK_RIGHT;
            velocity.x = 1;
        }
        else if(input == PlayerInput::PLAYER_INPUT_JUMP){
            grounded = false;
            velocity.y += 3.5f;
            current_movement = PlayerMovement::PLAYER_JUMP_NORMAL;
        }
        else{
            current_movement = PlayerMovement::PLAYER_IDLE;
            velocity.x = 0;
        }
    }

    if(current_movement != previous_movement){
        texture_index = animation_query[current_movement].index_min;
        animation_timer = 0;
    }

}
//----------------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------------
//MISC
//----------------------------------------------------------------------------------------------------
glm::vec2 Player::getGlobalCenter(){ return (getGlobalBL() + getGlobalBR()) /  2.0f; }
//--
glm::vec2 Player::getGlobalTL(){ return toVec2(mesh.vertices[2].Position) + position; }
glm::vec2 Player::getGlobalTR(){ return toVec2(mesh.vertices[3].Position) + position; }
glm::vec2 Player::getGlobalBL(){ return toVec2(mesh.vertices[1].Position) + position; }
glm::vec2 Player::getGlobalBR(){ return toVec2(mesh.vertices[0].Position) + position; }
//--
glm::vec2 Player::getVec_centre_to_top(){ return ((getGlobalTL() + getGlobalTR()) / 2.0f) - position; }
glm::vec2 Player::getVec_centre_to_bottom(){ return ((getGlobalBL() + getGlobalBR()) / 2.0f) - position; }
glm::vec2 Player::getVec_centre_to_left(){ return ((getGlobalTL() + getGlobalBL()) / 2.0f) - position; }
glm::vec2 Player::getVec_centre_to_right(){ return ((getGlobalTR() + getGlobalBR()) / 2.0f) - position; }
//----------------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------------
//DEBUGGING
//----------------------------------------------------------------------------------------------------
void Player::print(){
    printf("|----------------------------------------|\n");
    printf("|Movement :  %s             |\n", movement_toString(current_movement).c_str());
    printf("|FNet     :  <%+2.8f,%+2.8f> |\n",fNet.x,fNet.y);
    printf("|Velocity :  <%+2.8f,%+2.8f> |\n",velocity.x,velocity.y);
    printf("|Position :  <%+2.8f,%+2.8f> |\n",position.x,position.y);
    printf("|---------------------------S-------------|\n");
}
std::string Player::movement_toString(PlayerMovement movement){
    switch(movement){
        case PLAYER_IDLE:
            return "IDLE       ";

        case PLAYER_WALK_LEFT:
            return "WALK_LEFT  ";
        
        case PLAYER_WALK_RIGHT:
            return "WALK_RIGHT ";

        case PLAYER_JUMP_NORMAL:
            return "JUMP_NORMAL";
        
        case PLAYER_JUMP_LEFT:
            return "JUMP_LEFT  ";
        
        case PLAYER_JUMP_RIGHT:
            return "JUMP_RIGHT ";
        
        case PLAYER_FALL_NORMAL:
            return "FALL_NORMAL";
        
        case PLAYER_FALL_LEFT:
            return "FALL_LEFT  ";

        case PLAYER_FALL_RIGHT:
            return "FALL_RIGHT ";
    }
}
std::string Player::input_toString(PlayerInput input){

    switch(input){
        case PLAYER_INPUT_NONE:
            return "NONE";

        case PLAYER_INPUT_LEFT:
            return "LEFT";

        case PLAYER_INPUT_RIGHT: 
            return "RIGHT";

        case PLAYER_INPUT_JUMP:
            return "JUMP";
    }

}
//----------------------------------------------------------------------------------------------------