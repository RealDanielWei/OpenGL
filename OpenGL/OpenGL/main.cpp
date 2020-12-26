#include "GLWrapper.h"

using namespace std;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



int main()
{
    GLFWwindow* window = GLInit(SCR_WIDTH, SCR_HEIGHT, "App");
    
    float L = 0.5;
    
    float vertices[] = {
        //front
        L, 0, 0,    1.0,0.0,0.0,    0.25, 1.0/3,
        L, L, 0,    0.0,1.0,0.0,    0.25, 2.0/3,
        0, L, 0,    0.0,0.0,1.0,    0.5,  2.0/3,
        0, 0, 0,    1.0,0.0,0.0,    0.5,  1.0/3
        //left
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,
        1, 2, 3

    };

    Model model = Model();
    model.load(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]), "grass_brick.png");

    Shader shader = Shader("vshader", "fshader");
    
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(model.getVAO()); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6); // set the count to 6 since we're drawing 6 vertices now (2 triangles); not 3!
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    GLTerminate();
    return 0;
}



