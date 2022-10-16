#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Shader.h>
#include <Camera.h>
#include <Model.h>

#include <GameState.h>
GameState gamestate;

#include <init_glfw.h>
#include <input.h>



#include <iostream>

int main()
{
    // Init all GLFW/GLEW stuff and grab window*
    GLFWwindow* window = init_glfw(SCR_WIDTH, SCR_HEIGHT, "gengen");

    // Init player    
    player_ptr = new Player("models/player/boshy.obj");

    // build and compile shaders
    // -------------------------
    Shader shader("src/resources/vertex_shader.glsl", "src/resources/fragment_shader.glsl");

    // load models
    // -----------
    Model background("models/map/background.obj");
    Model ground("models/map/ground.obj");

    float sky_x_off = 0;
    float ground_x_off = 0;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        sky_x_off += 0.0025f * deltaTime;

        // input
        // -----
        processInput(window);

        if(player_ptr->position.x > 0.5f) ground_x_off = player_ptr->position.x - 0.5f;



        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // don't forget to enable shader before setting uniforms
        shader.use();

        // draw all

        shader.setVec2("uv_scale",glm::vec2(1,1));
        shader.setVec2("vertex_offset",glm::vec2(0,0));

        shader.setVec2("uv_offset",glm::vec2(sky_x_off,0) + player_ptr->map_offset * 0.01f);
        background.draw(shader);

        shader.setVec2("uv_offset",player_ptr->map_offset * 8.0f);
        ground.draw(shader);


        shader.setVec2("uv_offset",glm::vec2(0,0));
        shader.setVec2("vertex_offset",player_ptr->position);
        shader.setVec2("uv_scale",player_ptr->lookingRight ? glm::vec2(1,1) : glm::vec2(-1,1));
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

