#include "PlayerShader.h"

PlayerShader::PlayerShader()
    : BasicShader("Player", "Player")
{
    getUniforms();
}

void PlayerShader::getUniforms()
{
    BasicShader::getUniforms();
    
}
