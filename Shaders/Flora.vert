#version 330

layout(location = 0) in vec3  inVertexPosition;
layout(location = 1) in vec2  inTextureCoord;
layout(location = 2) in float inCardinalLight;

out vec2 passTextureCoord;
out float passCardinalLight;

uniform mat4 projViewMatrix;
uniform float globalTime;
uniform int isShade;
uniform vec3 rootPos;

vec4 getWorldPos()
{
    vec3 inVert = inVertexPosition.xyz;
    inVert.x += sin((globalTime + inVert.z + inVert.y) * 1.8f) / 15.0f;
    inVert.z -= cos((globalTime + inVert.x + inVert.y) * 1.8f) / 15.0f;
    return vec4(inVert, 1);
}


void main()
{
    float test;
         
    gl_Position = getWorldPos();
    test = gl_Position.y;
    
    if(isShade == 1){
        if(int(gl_Position.y)%2 == 1 ) {
            gl_Position.y-=0.9;
            gl_Position.x+=1;
        }
    }
    gl_Position = projViewMatrix * gl_Position;

    passTextureCoord    = inTextureCoord;
    
    passCardinalLight   = inCardinalLight;
    
    if(isShade == 1) {
        passCardinalLight *= 0.1f;
        if(inTextureCoord.x < 0.475f && inTextureCoord.x > 0.3f) passCardinalLight *= 0;
    }
}
