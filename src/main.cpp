#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"
#include "VertexBufferLayout.hpp"
#include "Texture.hpp"


int main() {
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }


    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "Unable to init glew" << std::endl;
        glfwTerminate();
    }


    std::cout << glGetString(GL_VERSION) << std::endl;

  

    float positions[8] = {  0.5f,  0.5f, 
                           -0.5f,  0.5f,
                           -0.5f, -0.5f,
                            0.5f, -0.5f };

    unsigned int indexArray[6] = {1, 2, 3, 0, 1, 3};


    VertexArray vArray;
    VertexBuffer vBuffer(positions, 4 * 2 * sizeof(float));
    VertexBufferLayout vBufferLayout;
    vBufferLayout.push<float>(2);
    vArray.addBuffer(vBuffer, vBufferLayout);

    IndexBuffer iBuffer(indexArray, 6);

    Shader shader("shaders/BasicShader.shader");
    shader.bind(); 
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    float incr2 = 0.02;
    float incr = 0.05f;
    float incr3 = 0.03f;
    shader.bind();
    shader.setUniform4f("uniformColor", r, g, b, 1.0f);

    Texture texture("src/resources/texture/texture.jpg");
    texture.bind();
    shader.setUniform1i("unifTexture", 0);
    
    


    vArray.unBind();
    vBuffer.unBind();
    iBuffer.unBind();
    shader.unBind();

    Renderer renderer;
    vBuffer.bind();


    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scanCode, int action, int mods) {
        switch (action) {
        case GLFW_PRESS:
            std::cout << "Key Pressed: " << key << ", " << scanCode;
            break;

        case GLFW_RELEASE:
            std::cout << "Key Released: " << key << ", " << scanCode;
            break;

        case GLFW_REPEAT:
            std::cout << "Key Repeated " << key << ", " << scanCode;
            break;
        }
        });

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
        std::cout << "(" << (float)x << ", " << (float)y << std::endl;
        });

       

    while (!glfwWindowShouldClose(window)) {
        
        renderer.clear();

        shader.bind();
        shader.setUniform4f("uniformColor", r, g, b, 1.0f);

        renderer.draw(vArray, iBuffer, shader);

        if (r > 1.0f)
            incr = -0.05f;
        else if(r < 0.0f)
            incr = 0.05f;
        if (g > 1.0f)
            incr2 = -0.04f;
        else if (r < 0.0f)
            incr2 = 0.04f;
        if (b > 1.0f)
            incr3 = -0.03f;
        else if (b < 0.0f)
            incr3 = 0.03f;
        
        r += incr;
        g += incr2;
        b += incr3;

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}