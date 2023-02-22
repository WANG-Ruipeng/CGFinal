#ifndef PLAYERSHADER_H_INCLUDED
#define PLAYERSHADER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>

#include "../Model.h"
#include "../Shaders/SkyboxShader.h"
#include "../Shaders/BasicShader.h"
#include "../Texture/CubeTexture.h"

class Camera;

class PlayerRenderer {
public:
    PlayerRenderer();

  void render(const Camera &camera);

private:
  Model m_playerModel;
  BasicShader m_shader;
  CubeTexture m_cubeTexture;
};

#endif // PLAYERRENDERER_H_INCLUDED
