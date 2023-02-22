#ifndef FLORASHADER_H_INCLUDED
#define FLORASHADER_H_INCLUDED

#include "BasicShader.h"

class FloraShader : public BasicShader {
  public:
    FloraShader();
    void loadTime(const float &time);
    void loadShadeMode(int isShade);

  private:
    void getUniforms() override;
    GLuint m_time;
    GLuint m_mode;
    int isShade;
};

#endif // FLORASHADER_H_INCLUDED
