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



#include <iostream>

int main()
{
/*
    Tri A(new glm::vec3(-1,-1,0),new glm::vec3(-1,1,0),new glm::vec3(1,-1,0));
    Tri Bi(new glm::vec3(-0.5f,0,0),new glm::vec3(1,0,0),new glm::vec3(1,1,0));
    Tri Bni(new glm::vec3(0.1f,0,0),new glm::vec3(1,0,0),new glm::vec3(1,1,0));

    if(!A.check_collision(&Bi)) printf("fail\n");
    else printf("pass\n");
    if(!A.check_collision(&Bni))printf("pass\n");
    else printf("fail\n");

    return -1;
*/
    // Init all GLFW/GLEW stuff and grab window*
    GLFWwindow* window = init_glfw(SCR_WIDTH, SCR_HEIGHT, "gengen");

    // Init player    
    player_ptr = new Player();
    Map map;

    glm::vec2 gravity(0,-9.81);
    glm::vec2 external_forces(0,0);
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

