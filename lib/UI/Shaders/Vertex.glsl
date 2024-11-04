#version 120

attribute vec3 position;
attribute vec3 color;

varying vec3 fragColor;

void main() {
    fragColor = color;
    gl_Position = vec4(position, 1.0);
}