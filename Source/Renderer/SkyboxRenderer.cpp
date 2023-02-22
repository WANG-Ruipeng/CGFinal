#include "SkyboxRenderer.h"

#include "../Camera.h"

#include <iostream>
//天空盒绘制
SkyboxRenderer::SkyboxRenderer()
{
    constexpr GLfloat SIZE = 500;
    std::vector<GLfloat> vertexCoords{
        // Back
        SIZE,
        -SIZE,
        -SIZE,
        -SIZE,
        -SIZE,
        -SIZE,
        -SIZE,
        SIZE,
        -SIZE,
        SIZE,
        SIZE,
        -SIZE,

        // Front
        -SIZE,
        -SIZE,
        SIZE,
        SIZE,
        -SIZE,
        SIZE,
        SIZE,
        SIZE,
        SIZE,
        -SIZE,
        SIZE,
        SIZE,

        // Right
        SIZE,
        -SIZE,
        SIZE,
        SIZE,
        -SIZE,
        -SIZE,
        SIZE,
        SIZE,
        -SIZE,
        SIZE,
        SIZE,
        SIZE,

        // Left
        -SIZE,
        -SIZE,
        -SIZE,
        -SIZE,
        -SIZE,
        SIZE,
        -SIZE,
        SIZE,
        SIZE,
        -SIZE,
        SIZE,
        -SIZE,

        // Top
        -SIZE,
        SIZE,
        SIZE,
        SIZE,
        SIZE,
        SIZE,
        SIZE,
        SIZE,
        -SIZE,
        -SIZE,
        SIZE,
        -SIZE,

        // Bottom
        -SIZE,
        -SIZE,
        -SIZE,
        SIZE,
        -SIZE,
        -SIZE,
        SIZE,
        -SIZE,
        SIZE,
        -SIZE,
        -SIZE,
        SIZE,
    };

    std::vector<GLuint> indices{0,  1,  2,  2,  3,  0,

                                4,  5,  6,  6,  7,  4,

                                8,  9,  10, 10, 11, 8,

                                12, 13, 14, 14, 15, 12,

                                16, 17, 18, 18, 19, 16,

                                20, 21, 22, 22, 23, 20}; //天空盒绘制的点顺序

    m_skyCube.genVAO();
    m_skyCube.addVBO(3, vertexCoords);
    m_skyCube.addEBO(indices);

    m_cubeTexture.loadFromFiles({
        "dm",
        "dm",
        "dt",
        "db",
        "dm",
        "dm",
    });
}

void SkyboxRenderer::render(const Camera &camera)
{
    m_shader.useProgram();
    m_skyCube.bindVAO();
    m_cubeTexture.bindTexture();

    m_shader.loadViewMatrix(camera.getViewMatrix());
    m_shader.loadProjectionMatrix(camera.getProjMatrix());

    GL::drawElements(m_skyCube.getIndicesCount());
}
