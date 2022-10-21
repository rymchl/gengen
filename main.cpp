/*#include "src/headers/Misc.h"
int main(){

    Tri tri(new glm::vec3(0,-1,0), new glm::vec3(1,-1,0), new glm::vec3(1,0,0));

    Intersection i0 = find_intersection(glm::vec2(-1,1),glm::vec2(2,-2),glm::vec2(0,-1),glm::vec2(1,1));
    i0.print();

    Intersection i1 = find_min_intersection(glm::vec2(-1,1),glm::vec2(2,-2),tri);
    i1.print();

    return 0;
}*/
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Shader.h>
#include <Camera.h>
#include <Model.h>
#include <Map.h>

#include <GameState.h>
GameState gamestate;

#include <init_glfw.h>
#include <input.h>

#include <unistd.h>
#include <iostream>


int main()
{
    // Init all GLFW/GLEW stuff and grab window*
    GLFWwindow* window = init_glfw(SCR_WIDTH, SCR_HEIGHT, "gengen");

    // Init player    
    player_ptr = new Player();
    Map map;

    // build and compile shaders
    // -------------------------
    Shader shader("src/resources/vertex_shader.glsl", "src/resources/fragment_shader.glsl");
    // render loop
    // -----------

    lastFrame = static_cast<float>(glfwGetTime());
    while (!glfwWindowShouldClose(window))
    {

        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;



        player_ptr->animate(deltaTime);
        map.time_offset += deltaTime;
                

        // input
        // -----
        processInput(window);

        // physics
        // ------
        player_ptr->handle_physics(deltaTime,map.terrain_meshes);
        
        if(player_ptr->grounded) printf("GROUNDED\n");
        else printf("IN AIR\n");

        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // don't forget to enable shader before setting uniforms
        shader.use();
        // draw all
        map.draw(shader,player_ptr->map_offset);
        player_ptr->draw(shader);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}
