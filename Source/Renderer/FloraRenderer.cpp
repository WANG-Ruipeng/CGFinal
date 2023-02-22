#include "FloraRenderer.h"

#include "../Application.h"
#include "../Camera.h"
#include "../World/Block/BlockDatabase.h"
#include "../World/Chunk/ChunkMesh.h"

#include <iostream>

void FloraRenderer::add(const ChunkMesh &mesh)
{
    m_chunks.push_back(&mesh.getModel().getRenderInfo());
}

void FloraRenderer::render(const Camera &camera,int isShade)
{
    
    if (m_chunks.empty()) {
        return;
    }

    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    m_shader.useProgram();
    
    m_shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());
    m_shader.loadTime(g_timeElapsed);
    m_shader.loadShadeMode(isShade);
    
    for (auto mesh : m_chunks) {
        GL::bindVAO(mesh->vao);
        //std::cout << mesh->vao << ' ' << mesh->indicesCount << std::endl;
        GL::drawElements(mesh->indicesCount);
    }

    if(isShade == 1) m_chunks.clear();
}
