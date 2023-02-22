#include "FloraShader.h"
#include <iostream>

FloraShader::FloraShader()
    : BasicShader("Flora", "Chunk")
{
    getUniforms();
}

void FloraShader::loadTime(const float &time)
{
    loadFloat(m_time, time);
}

void FloraShader::getUniforms()
{
    BasicShader::getUniforms();
    m_time = glGetUniformLocation(m_id, "globalTime");
}

void FloraShader::loadShadeMode(int isShade){
    m_mode = glGetUniformLocation(m_id,"isShade");
    loadInt(m_mode, isShade);
    //std::cout <<m_id<< std::endl;
}

