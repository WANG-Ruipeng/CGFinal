#version 330

out vec4 outColour;
//in  vec2 passTextureCoord;
in vec3 color;

//uniform sampler2D texSampler;


void main()
{
    //vec4 color = texture(texSampler, passTextureCoord);
    //color = vec4(0.3,0.3,0.7,1.0);
    outColour = vec4(color,1.0);
}
