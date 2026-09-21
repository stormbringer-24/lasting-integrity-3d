#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned int loadTexture(char const *path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);

    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

Vertex towerVertices[] = {
    {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
    {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
    {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},

    {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
    {{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
    {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
    {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},

    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
    {{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
    {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
    {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
    {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},

    {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{-0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
    {{-0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
    {{-0.5f, 0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
    {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},

    {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
    {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
    {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
    {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
    {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},

    {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
    {{0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
    {{0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
    {{0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
    {{-0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
    {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}}};

float quadVertices[] = {
    -1.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f,
    1.0f, -1.0f, 1.0f, 0.0f,

    -1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, -1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 1.0f};

int main()
{
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lasting Integrity", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        return -1;

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader beadShader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    Shader towerShader("shaders/tower_vertex.glsl", "shaders/tower_fragment.glsl");
    Shader skyShader("shaders/sky_vertex.glsl", "shaders/sky_fragment.glsl");
    Shader sprenShader("shaders/spren_vertex.glsl", "shaders/spren_fragment.glsl");

    int gridResolution = 2500;
    int numBeads = gridResolution * gridResolution;
    std::vector<float> beads;
    beads.reserve(numBeads * 3);

    float scale = 10.0f;
    for (int i = 0; i < gridResolution; i++)
    {
        for (int j = 0; j < gridResolution; j++)
        {
            float x = (((float)i / (gridResolution - 1)) * 2.0f - 1.0f) * scale;
            float z = (((float)j / (gridResolution - 1)) * 2.0f - 1.0f) * scale;

            beads.push_back(x);
            beads.push_back(0.0f);
            beads.push_back(z);
        }
    }

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, beads.size() * sizeof(float), beads.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    unsigned int towerVAO, towerVBO;
    glGenVertexArrays(1, &towerVAO);
    glGenBuffers(1, &towerVBO);

    glBindVertexArray(towerVAO);
    glBindBuffer(GL_ARRAY_BUFFER, towerVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(towerVertices), towerVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);

    const int NUM_SPRENS = 200;
    float sprenIndices[NUM_SPRENS];
    for (int i = 0; i < NUM_SPRENS; i++)
        sprenIndices[i] = (float)i;

    unsigned int sprenVAO, sprenVBO;
    glGenVertexArrays(1, &sprenVAO);
    glGenBuffers(1, &sprenVBO);
    glBindVertexArray(sprenVAO);
    glBindBuffer(GL_ARRAY_BUFFER, sprenVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sprenIndices), sprenIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    unsigned int quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));

    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.3f, 10.0f);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(cameraPosition, glm::vec3(0.0f, 2.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-3.5f, -1.5f, -15.0f));
    model = glm::rotate(model, glm::radians(35.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(4.0f, 30.0f, 4.0f));
    glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(model)));

    unsigned int diffuseMap = loadTexture("textures/rock_diffuse1.JPG");
    unsigned int cloudMap = loadTexture("textures/clouds.JPG");

    towerShader.use();
    glUniform1i(glGetUniformLocation(towerShader.ID, "diffuseMap"), 0);

    skyShader.use();
    glUniform1i(glGetUniformLocation(skyShader.ID, "cloudMap"), 0);

    GLint locBeadProj = glGetUniformLocation(beadShader.ID, "projection");
    GLint locBeadView = glGetUniformLocation(beadShader.ID, "view");
    GLint locBeadPos = glGetUniformLocation(beadShader.ID, "viewPos");
    GLint locBeadTime = glGetUniformLocation(beadShader.ID, "u_time");

    GLint locTowerProj = glGetUniformLocation(towerShader.ID, "projection");
    GLint locTowerView = glGetUniformLocation(towerShader.ID, "view");
    GLint locTowerModel = glGetUniformLocation(towerShader.ID, "model");
    GLint locNormalMatrix = glGetUniformLocation(towerShader.ID, "normalMatrix");

    GLint locSprenProj = glGetUniformLocation(sprenShader.ID, "projection");
    GLint locSprenView = glGetUniformLocation(sprenShader.ID, "view");
    GLint locSprenTime = glGetUniformLocation(sprenShader.ID, "u_time");
    GLint locSkyTime = glGetUniformLocation(skyShader.ID, "u_time");

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        float currentTime = (float)glfwGetTime();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDepthMask(GL_FALSE);
        skyShader.use();
        glUniform1f(locSkyTime, currentTime);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cloudMap);
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDepthMask(GL_TRUE);

        beadShader.use();
        glUniformMatrix4fv(locBeadProj, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(locBeadView, 1, GL_FALSE, glm::value_ptr(view));
        glUniform3f(locBeadPos, cameraPosition.x, cameraPosition.y, cameraPosition.z);
        glUniform1f(locBeadTime, currentTime);
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, numBeads);

        towerShader.use();
        glUniformMatrix4fv(locTowerProj, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(locTowerView, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix3fv(locNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);

        glUniformMatrix4fv(locTowerModel, 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(towerVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        sprenShader.use();
        glUniformMatrix4fv(locSprenProj, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(locSprenView, 1, GL_FALSE, glm::value_ptr(view));
        glUniform1f(locSprenTime, currentTime);
        glBindVertexArray(sprenVAO);
        glDrawArrays(GL_POINTS, 0, NUM_SPRENS);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &sprenVAO);
    glDeleteBuffers(1, &sprenVBO);
    glDeleteVertexArrays(1, &towerVAO);
    glDeleteBuffers(1, &towerVBO);
    glfwTerminate();
    return 0;
}
