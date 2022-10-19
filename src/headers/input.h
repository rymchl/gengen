#ifndef INPUT
#define INPUT

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    bool input = false;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
        input = true;
    }
        
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        player_ptr->ProcessKeyboard(PlayerMovement::PLAYER_LEFT, deltaTime);
        input = true;
    }
        
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        player_ptr->ProcessKeyboard(PlayerMovement::PLAYER_RIGHT, deltaTime);
        input = true;
    }
        
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        player_ptr->ProcessKeyboard(PlayerMovement::PLAYER_UP, deltaTime);
        input = true;
    }
        
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        
        input = true;
    }

    if(!input) player_ptr->ProcessKeyboard(PlayerMovement::PLAYER_IDLE, deltaTime);
        
    
        
    
    /*
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.ProcessKeyboard(SHIFT, deltaTime);
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
        camera.ProcessKeyboard(UNSHIFT, deltaTime);
    */

    
}

#endif