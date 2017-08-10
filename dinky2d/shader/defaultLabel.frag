#version 410
uniform sampler2D tex;
in vec2 texCoord;
uniform vec4 fragColor;
out vec4 outputColor;
void main(void)
{
    outputColor = fragColor * vec4(1.0, 1.0, 1.0, texture(tex, texCoord).r);
}
