#ifndef PLAYERSHADER_H_INCLUDED
#define PLAYERSHADER_H_INCLUDED

#include "BasicShader.h"

class PlayerShader : public BasicShader {
  public:
    PlayerShader();

  private:
    void getUniforms() override;
};

#endif // PLAYERSHADER_H_INCLUDED
