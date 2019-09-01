#version 450 core

layout (location = 0) in vec4 pos;


void main() {
    gl_Position = pos;// * vec4(0.25, 0.25, 0.25, 1);
}
