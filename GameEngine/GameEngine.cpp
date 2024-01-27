// GameEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == true) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Game Engine", NULL, NULL);
    if (!window) {

        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    std::cout << "Hello World!\n";
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }
  

    // A render loop so the window wont be closed immediately.
    while (!glfwWindowShouldClose(window)) {
        // input
        processInput(window);

        // rendering commands

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window); // will swap the color buffer
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}


