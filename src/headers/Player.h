#ifndef PLAYER
#define PLAYER

#include <iostream>
#include <Model.h>
#include <Intersection.h>
#include <Tri.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <unordered_map>

enum PlayerMovement{
    PLAYER_IDLE = 0,
    PLAYER_WALK_LEFT,
    PLAYER_WALK_RIGHT,
    PLAYER_JUMP_NORMAL,
    PLAYER_JUMP_LEFT,
    PLAYER_JUMP_RIGHT,
    PLAYER_FALL_NORMAL,
    PLAYER_FALL_LEFT,
    PLAYER_FALL_RIGHT
};

enum PlayerInput{
    PLAYER_INPUT_NONE = 0,
    PLAYER_INPUT_LEFT,
    PLAYER_INPUT_RIGHT,
    PLAYER_INPUT_JUMP,
};

enum CycleStyle{
    CYCLE_NONE = 0,
    CYCLE_RESTART, //play til end then reset
    CYCLE_REVERSE //play til end then reverse
};

class Player{

    public:

        //VARS
        //------------------------------------------------------------------
        PlayerMovement current_movement = PlayerMovement::PLAYER_IDLE;
        glm::vec2 map_offset;
        glm::vec2 position;
        glm::vec2 velocity;
        bool grounded;
        float width;
        float animation_timer;
        //------------------------------------------------------------------
        

        //CONSTRUCTION
        //------------------------------------------------------------------
        Player();
        //------------------------------------------------------------------


        //PHYSICS AND TRANSFORMATIONS
        //------------------------------------------------------------------
        void move(glm::vec2 dp);
        void apply_force(float x, float y);
        void apply_force(glm::vec2 f) {apply_force(f.x,f.y);}
        void step_physics(float dT, std::vector<Mesh*> collision_meshes);
        void handle_physics(float dT, std::vector<Mesh*> collision_meshes);
        void handle_collisions(std::vector<Mesh*> terrain);
        glm::vec2 get_collision_offset(Tri& tri);
        //------------------------------------------------------------------
        
        //GRAPHICS
        //------------------------------------------------------------------
        void animate(float deltaTime);
        void draw(Shader& shader);
        //------------------------------------------------------------------

        //INPUT PROCESSING
        //------------------------------------------------------------------
        void processInput(GLFWwindow *window, float deltaTime);
        //------------------------------------------------------------------


        //DEBUGGING
        //------------------------------------------------------------------
        void print();
        std::string movement_toString(PlayerMovement movement);
        std::string input_toString(PlayerInput input);
        //------------------------------------------------------------------
        
        //MISC
        //------------------------------------------------------------------
        glm::vec2 getGlobalCenter();
        glm::vec2 getGlobalTL();
        glm::vec2 getGlobalTR();
        glm::vec2 getGlobalBL();
        glm::vec2 getGlobalBR();
        glm::vec2 getVec_centre_to_top();
        glm::vec2 getVec_centre_to_bottom();
        glm::vec2 getVec_centre_to_left();
        glm::vec2 getVec_centre_to_right();
        //------------------------------------------------------------------


    private:
        //VARS
        //------------------------------------------------------------------
        Mesh mesh;
        glm::vec2 prev_position;
        glm::vec2 fNet;
        struct AnimationData{
            AnimationData(){
                index_min = 0;
                index_max = 0;
                period = 0;
                reverse = false;
                style = CycleStyle::CYCLE_NONE;
            }
            AnimationData(int min, int max){
                period = 0.25f / (max - min);
                index_min = min;
                index_max = max;
                style = CycleStyle::CYCLE_NONE;
            }
            AnimationData(int min, int max, CycleStyle style_in){
                period = 0.75f / (max - min);
                index_min = min;
                index_max = max;
                style = style_in;
            }
            
            unsigned int index_min = 0;
            unsigned int index_max = 0;
            float period = 0;
            bool reverse = false;
            CycleStyle style;
        };
        std::unordered_map<PlayerMovement,AnimationData> animation_query;
        unsigned int texture_index;
        //------------------------------------------------------------------

        //INPUT PROCESSING
        //------------------------------------------------------------------
        void processMovement(PlayerInput direction, float deltaTime);
        //------------------------------------------------------------------
};

#endif