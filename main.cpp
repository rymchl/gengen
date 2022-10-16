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
    while (!glfwWindowShouldClose(window))
    {

        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        map.time_offset += deltaTime;

        // input
        // -----
        processInput(window);

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

