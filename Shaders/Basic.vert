#version 330

layout(location = 0) in vec3 inVertexPosition;
layout(location = 1) in vec2 inTextureCoord;

//out vec2 passTextureCoord;
out vec3 color;

uniform mat4 projViewMatrix;
uniform mat4 modelMatrix;
uniform int colorIndex;

void main()
{
    gl_Position = projViewMatrix * modelMatrix * vec4(inVertexPosition, 1.0);
    
    //passTextureCoord = inTextureCoord;
    switch(colorIndex){
        case 0 :
            color = vec3(0.8,0.0,0.0);
            break;
        case 1 :
            color = vec3(0.0,0.8,0.0);
            break;
        case 2 :
            color = vec3(0.0,0.0,0.8);
            break;
        case 3 :
            color = vec3(0.0,0.8,0.8);
            break;
        case 4 :
            color = vec3(0.8,0.0,0.8);
            break;
        case 5 :
            color = vec3(0.8,0.8,0.0);
            break;
        default :
            color = vec3(0.0,0.0,0.0);
            break;
    }
}
