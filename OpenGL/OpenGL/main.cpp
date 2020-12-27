#include "GLWrapper.h"

using namespace std;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));


int main()
{
    GLFWwindow* window = GLInit(SCR_WIDTH, SCR_HEIGHT, "App");
    
    float L = 0.5;
    
    float vertices[] = {
        //front
        L, 0, 0,    1.0,0.0,0.0,    0.25, 1.0/3,
        L, L, 0,    0.0,1.0,0.0,    0.25, 2.0/3,
        0, L, 0,    0.0,0.0,1.0,    0.5,  2.0/3,
        0, 0, 0,    1.0,0.0,0.0,    0.5,  1.0/3,
        //left
        L, 0, L,    1.0,0.0,0.0,    0.0, 1.0 / 3,
        L, L, L,    0.0,1.0,0.0,    0.0, 2.0 / 3,
        L, L, 0,    0.0,0.0,1.0,    0.25,  2.0 / 3,
        L, 0, 0,    1.0,0.0,0.0,    0.25,  1.0 / 3,
        //right
        0, 0, 0,    1.0,0.0,0.0,    0.5, 1.0 / 3,
        0, L, 0,    0.0,1.0,0.0,    0.5, 2.0 / 3,
        0, L, L,    0.0,0.0,1.0,    0.75,  2.0 / 3,
        0, 0, L,    1.0,0.0,0.0,    0.75,  1.0 / 3,
        //top
        L, L, 0,    1.0,0.0,0.0,    0.25, 2.0 / 3,
        L, L, L,    0.0,1.0,0.0,    0.25, 1.0,
        0, L, L,    0.0,0.0,1.0,    0.5,  1.0,
        0, L, 0,    1.0,0.0,0.0,    0.5,  2.0 / 3,
        //bottom
        L, 0, L,    1.0,0.0,0.0,    0.25, 0.0,
        L, 0, 0,    0.0,1.0,0.0,    0.25, 1.0 / 3,
        0, 0, 0,    0.0,0.0,1.0,    0.5,  1.0 / 3,
        0, 0, L,    1.0,0.0,0.0,    0.5,  0.0,
        //back
        0, 0, L,    1.0,0.0,0.0,    0.75, 1.0 / 3,
        0, L, L,    0.0,1.0,0.0,    0.75, 2.0 / 3,
        L, L, L,    0.0,0.0,1.0,    1.0,  2.0 / 3,
        L, 0, L,    1.0,0.0,0.0,    1.0,  1.0 / 3
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,
        1, 2, 3,
        4, 5, 7,
        5, 6, 7,
        8, 9, 11,
        9, 10, 11,
        12,13,15,
        13,14,15,
        16,17,19,
        17,18,19,
        20,21,23,
        21,22,23
    };

    Model amodel = Model();
    amodel.load(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]), "grass_brick.png");

    Shader shader = Shader("vshader", "fshader");
    

    double currentTime = 0.0, lastTime = 0.0;
    int n = 0, N = 10000;
    while (!glfwWindowShouldClose(window))
    {
        processKeyBoardInput(camera, window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        glm::mat4 model = glm::mat4(1.0f);
        shader.setMat4("model", model);

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        shader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        shader.setMat4("view", view);

        glBindVertexArray(amodel.getVAO()); 

        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
        //measure fps
        n++;
        if (n >= N) {
            n = 0;
            currentTime = glfwGetTime();
            cout << "Fps: " << N / (currentTime - lastTime) << endl;
            lastTime = currentTime;
        }
    }

    GLTerminate();
    return 0;
}



