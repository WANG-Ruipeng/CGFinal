#include "PlayerRenderer.h"
#include "../Shaders/Angel.h"

#include "../Application.h"
#include "../Camera.h"
#include "../World/Block/BlockDatabase.h"
#include "../World/Chunk/ChunkMesh.h"

#include <iostream>
#include <stack>
using namespace std;

//GLuint InitShader(const char* vShaderFile, const char* fShaderFile);

PlayerRenderer::PlayerRenderer()
{
    constexpr GLfloat SIZE = 1;
    std::vector<GLfloat> vertexCoords{
        // Back
        SIZE,-SIZE,-SIZE,-SIZE,-SIZE,-SIZE,-SIZE,SIZE,-SIZE,SIZE,SIZE,-SIZE,

        // Front
        -SIZE,-SIZE,SIZE,SIZE,-SIZE,SIZE,SIZE,SIZE,SIZE,-SIZE,SIZE,SIZE,

        // Right
        SIZE,-SIZE,SIZE,SIZE,-SIZE,-SIZE,SIZE,SIZE,-SIZE,SIZE,SIZE,SIZE,

        // Left
        -SIZE,-SIZE,-SIZE,-SIZE,-SIZE,SIZE,-SIZE,SIZE,SIZE,-SIZE,SIZE,-SIZE,

        // Top
        -SIZE,SIZE,SIZE,SIZE,SIZE,SIZE,SIZE,SIZE,-SIZE,-SIZE,SIZE,-SIZE,

        // Bottom
        -SIZE,-SIZE,-SIZE,SIZE,-SIZE,-SIZE,SIZE,-SIZE,SIZE,-SIZE,-SIZE,SIZE,
    };

    std::vector<GLuint> indices{0,  1,  2,  2,  3,  0,

                                4,  5,  6,  6,  7,  4,

                                8,  9,  10, 10, 11, 8,

                                12, 13, 14, 14, 15, 12,

                                16, 17, 18, 18, 19, 16,

                                20, 21, 22, 22, 23, 20};

    m_playerModel.genVAO();
    m_playerModel.addVBO(3, vertexCoords);
    m_playerModel.addEBO(indices);

    //m_cubeTexture.loadFromFiles({"top","dm","dt","db","dm","dm",});
    
    
}

void PlayerRenderer::render(const Camera &camera)
{
    m_shader.useProgram();
    m_playerModel.bindVAO();
    //m_cubeTexture.bindTexture();
    
    float theta = 0;
    if(camera.wasdKey[1]==1)
        theta += 45;
    if(camera.wasdKey[3]==1)
        theta -= 45;
    bool isMovingForward = false;
    if(camera.wasdKey[0]==1||camera.wasdKey[1]==1||camera.wasdKey[3]==1) isMovingForward = true;
    bool small = false;
    if((camera.wasdKey[0]==1&&camera.wasdKey[2]==1)||(camera.wasdKey[1]==1&&camera.wasdKey[3]==1)) small = true;
    bool isMovingBackward = false;
    if(camera.wasdKey[2]==1) isMovingBackward = true;
    stack<glm::mat4> matrixStack;
 
    glm::vec3 playerLoc = camera.m_pEntity->position;
    glm::mat4 modelMatrix = glm::mat4(1.0);
    glm::mat4 instance = glm::mat4(1.0);
    playerLoc.y += 0.9;
    
    //头
    modelMatrix = glm::translate(modelMatrix,playerLoc);
    //rotate
    
    //translate
    instance = glm::scale(modelMatrix, glm::vec3(0.1));
    m_shader.loadModelMatrix(instance);
    m_shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());
    m_shader.loadColorIndex(0);
    GL::drawElements(m_playerModel.getIndicesCount());
    instance = glm::mat4(1.0);
    
    //身体
    matrixStack.push(modelMatrix);
    modelMatrix = glm::translate(modelMatrix,glm::vec3(0,-0.45,0));
    modelMatrix = glm::rotate(modelMatrix,glm::radians(theta), glm::vec3(0.0, 1.0, 0.0));
    
    //translate
    instance = glm::scale(modelMatrix, glm::vec3(0.1,0.35,0.2));
    m_shader.loadModelMatrix(instance);
    m_shader.loadColorIndex(1);
    GL::drawElements(m_playerModel.getIndicesCount());
    instance = glm::mat4(1.0);
    
    //左手上半
    matrixStack.push(modelMatrix);
    modelMatrix = glm::translate(modelMatrix,glm::vec3(0,0.15,0.3));
    if(isMovingForward)
        modelMatrix = glm::rotate(modelMatrix, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));
    if(isMovingBackward)
        modelMatrix = glm::rotate(modelMatrix, glm::radians(-45.0f), glm::vec3(0.0, 0.0, 1.0));
    
    instance = glm::translate(modelMatrix,glm::vec3(0,-0.1,0.0));
    instance = glm::scale(instance, glm::vec3(0.07,0.2,0.07));
    m_shader.loadModelMatrix(instance);
    m_shader.loadColorIndex(2);
    GL::drawElements(m_playerModel.getIndicesCount());
    instance = glm::mat4(1.0);
    
    //左手下半
    matrixStack.push(modelMatrix);
    modelMatrix = glm::translate(modelMatrix,glm::vec3(0,-0.3,0.0));
    if(small)
        modelMatrix = glm::rotate(modelMatrix, glm::radians(-45.0f), glm::vec3(0.0, 0.0, 1.0));
    
    instance = glm::translate(modelMatrix,glm::vec3(0,-0.1,0.0));
    instance = glm::scale(instance, glm::vec3(0.03,0.1,0.03));
    m_shader.loadModelMatrix(instance);
    m_shader.loadColorIndex(3);
    GL::drawElements(m_playerModel.getIndicesCount());
    instance = glm::mat4(1.0);
    
    matrixStack.pop();
    modelMatrix = matrixStack.top();
    matrixStack.pop();
    
    //右手上半
    matrixStack.push(modelMatrix);
    modelMatrix = glm::translate(modelMatrix,glm::vec3(0,0.15,-0.3));
    if(isMovingForward)
        modelMatrix = glm::rotate(modelMatrix, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));
    if(isMovingBackward)
        modelMatrix = glm::rotate(modelMatrix, glm::radians(-45.0f), glm::vec3(0.0, 0.0, 1.0));
    
    
    instance = glm::translate(modelMatrix,glm::vec3(0,-0.1,0.0));
    instance = glm::scale(instance, glm::vec3(0.07,0.2,0.07));
    m_shader.loadModelMatrix(instance);
    m_shader.loadColorIndex(2);
    GL::drawElements(m_playerModel.getIndicesCount());
    instance = glm::mat4(1.0);
    
    //右手下半
    matrixStack.push(modelMatrix);
    modelMatrix = glm::translate(modelMatrix,glm::vec3(0,-0.3,0.0));
    if(small)
        modelMatrix = glm::rotate(modelMatrix, glm::radians(-45.0f), glm::vec3(0.0, 0.0, 1.0));
    
    instance = glm::translate(modelMatrix,glm::vec3(0,-0.1,0.0));
    instance = glm::scale(instance, glm::vec3(0.03,0.1,0.03));
    m_shader.loadModelMatrix(instance);
    m_shader.loadColorIndex(3);
    GL::drawElements(m_playerModel.getIndicesCount());
    instance = glm::mat4(1.0);
    
    matrixStack.pop();
    modelMatrix = matrixStack.top();
    matrixStack.pop();
    
    //左腿
    matrixStack.push(modelMatrix);
    modelMatrix = glm::translate(modelMatrix,glm::vec3(0,-0.4,-0.09));
    if(isMovingForward)
        modelMatrix = glm::rotate(modelMatrix, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));
    if(isMovingBackward)
        modelMatrix = glm::rotate(modelMatrix, glm::radians(-45.0f), glm::vec3(0.0, 0.0, 1.0));
    
    instance = glm::translate(modelMatrix,glm::vec3(0,-0.4,0.0));
    instance = glm::scale(instance, glm::vec3(0.07,0.4,0.07));
    m_shader.loadModelMatrix(instance);
    m_shader.loadColorIndex(4);
    GL::drawElements(m_playerModel.getIndicesCount());
    instance = glm::mat4(1.0);
    
    modelMatrix = matrixStack.top();
    matrixStack.pop();
    
    //右腿
    matrixStack.push(modelMatrix);
    modelMatrix = glm::translate(modelMatrix,glm::vec3(0,-0.4,+0.09));
    if(isMovingForward)
        modelMatrix = glm::rotate(modelMatrix, glm::radians(-45.0f), glm::vec3(0.0, 0.0, 1.0));
    if(isMovingBackward)
        modelMatrix = glm::rotate(modelMatrix, glm::radians(+45.0f), glm::vec3(0.0, 0.0, 1.0));
    
    instance = glm::translate(modelMatrix,glm::vec3(0,-0.4,0.0));
    instance = glm::scale(instance, glm::vec3(0.07,0.4,0.07));
    m_shader.loadModelMatrix(instance);
    m_shader.loadColorIndex(5);
    GL::drawElements(m_playerModel.getIndicesCount());
    instance = glm::mat4(1.0);
}
