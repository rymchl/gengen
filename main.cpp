#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Shader.h>
#include <Camera.h>
#include <Model.h>

#include <init_glfw.h>
#include <input.h>

#include <iostream>

int main()
{
    std::cout << "hey\n";
    return -1;
    // Init all GLFW/GLEW stuff and grab window*
    GLFWwindow* window = init_glfw(SCR_WIDTH, SCR_HEIGHT, "gengen");

    // build and compile shaders
    // -------------------------
    Shader shader("src/resources/vertex_shader.glsl", "src/resources/fragment_shader.glsl");

    // load models
    // -----------
    Model background("models/map/background.obj");
    Model ground("models/map/ground.obj");

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;


        // input
        // -----
        processInput(window);

        shader.setVec3("cameraPos",camera.Position);

        
        shader.setVec3("lightPos",player.position + glm::vec3(0,0.25f,0));

        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // don't forget to enable shader before setting uniforms
        shader.use();

        // view/projection transformations
        
        glm::mat4 projection(1,0,0,0,
                             0,1,0,0,
                             0,0,0,0,
                             0,0,0,1);
        
        //glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); 
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	
        shader.setMat4("model", model);
        background.draw(shader);
        ground.draw(shader);

        //draw player
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); 
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	
        model = glm::rotate(model, player.rotation, glm::vec3(0,1,0));
        shader.setMat4("model", model);
        player.draw(shader);

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

