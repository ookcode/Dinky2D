#version 410
layout(location = 0) in vec3 a_position;
uniform mat4 projection;
void main(void)
{
    gl_Position = projection * vec4(a_position, 1.0f);
}
