#version 450 core

layout (location = 0) in vec4 pos;

layout (location = 1) in vec4 in_color;

uniform mat4 model;
uniform mat4 vp;

out vec4 vertColor;

void main() {


    vertColor = in_color;

    gl_Position = vp * model * pos;
}
