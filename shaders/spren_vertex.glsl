#version 410 core
layout (location = 0) in float aIndex;

uniform float u_time;
uniform mat4 projection;
uniform mat4 view;

out float vBrightness;
out vec3 vColor;

float rand(float seed) {
    return fract(sin(seed * 127.1 + 311.7) * 43758.5453);
}

void main() {
    float i = aIndex;

    float orbitRadius  = 0.6 + rand(i*1.1)*3.0;  //distance from tower center
    float orbitHeight  = rand(i * 2.3)*15.0-4.0; //high
    float speedH       = 0.3 + rand(i*3.7)*0.8; 
    float speedV = rand(i * 23.1) < 0.3
        ? 0.8 + rand(i * 4.1) * 1.2       
        : 0.15 + rand(i * 4.1) * 0.3;     
    float phaseH       = rand(i*5.3)*6.2832;     
    float phaseV       = rand(i*6.9)*6.2832;     
    float bobAmp       = 0.2+rand(i*7.2) * 0.5; 

    float angleH = u_time * speedH + phaseH;
    float x = cos(angleH) * orbitRadius;
    float z = sin(angleH) * orbitRadius;
    float y = orbitHeight + sin(u_time * speedV + phaseV) * bobAmp;

    vec3 towerCenter = vec3(-3.5, 2.5, -15.0);
    vec3 worldPos = towerCenter + vec3(x, y, z);

    float flicker1 = sin(u_time * (2.0 + rand(i * 8.1) * 4.0) + rand(i * 9.3) * 6.28);
    float flicker2 = sin(u_time * (5.0 + rand(i * 2.7) * 3.0) + rand(i * 1.7) * 6.28);
    vBrightness = 0.5 + 0.3 * flicker1 + 0.2 * flicker2;
    vBrightness = clamp(vBrightness, 0.1, 1.0);

    float colorSeed = rand(i * 13.7);
    if (colorSeed < 0.45) {
        vColor = vec3(0.85, 0.93, 1.0);  
    } else if (colorSeed < 0.75) {
        vColor = vec3(0.6, 0.82, 1.0);   
    } else {
        vColor = vec3(0.82, 0.95, 0.8);   
    }

   float sizeSeed = rand(i * 23.1);
    gl_PointSize = sizeSeed < 0.3
        ? 1.5 + vBrightness * 2.0
        : 4.0 + vBrightness * 5.0;
    gl_Position = projection * view * vec4(worldPos, 1.0);
}