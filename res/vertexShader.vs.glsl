#version 330 core

layout (location = 0) in vec3 pointPosition;
layout (location = 1) in float pointIntensity;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out float intensity;

void main()
{
    intensity = pointIntensity;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pointPosition, 1.0);
}