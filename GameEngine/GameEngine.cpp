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

// Vertex Shader: Stage one of graphics pipline
void vertexShader(unsigned int &vertexShader) {
    int success;
    char infoLog[512];
    // Triangle
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    // Shader Language GLSL
    const char* vertexShaderSource = "#version 330 core\n" 
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    vertexShader;
    // Allocate memory on GPU and assign a bufferID to the variable VBO.
    unsigned int VBO;
    
    glGenBuffers(1, &VBO);

    // Bind the newly create Buffer to GL_ARRAY_BUFFER target.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::VERTEXSHADER::COMPILATION::FAILED\n" << infoLog << endl;
    }
}

void fragmentShader(unsigned int &fragmentShader) {
    int success;
    char infoLog[512];
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::FRAGMENTSHADER::COMPILATION::FAILED\n" << infoLog << endl;
    }
}

void shaderProgram(unsigned int &shaderProgram, unsigned int &vertexShader, unsigned int &fragmentShader) {
    int success;
    char infoLog[512];
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check program linking status.
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADERPROGRAM::COMPILATION::FAILED\n" << infoLog << endl;
    }

    // Delete the shaders after linking;
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

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
  
    unsigned int vertexShader_;
    unsigned int fragmentShader_;
    vertexShader(vertexShader_);
    fragmentShader(fragmentShader_);

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


