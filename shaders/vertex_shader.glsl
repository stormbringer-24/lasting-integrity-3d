#version 410 core
layout (location = 0) in vec3 aPos;
uniform float u_time;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPosWorld;

void main() {
    vec3 pos = aPos;

    float wave1 = sin(pos.x * 2.0 + u_time * 1.5) * 0.08; 
    float wave2 = sin(pos.x * 3.0 - pos.z * 2.0 + u_time * 1.0) * 0.05;
    float wave3 = sin((pos.x + pos.z) * 10.0 + u_time * 3.5) * 0.03;
    float wave4 = sin(pos.x * 1.5 + pos.z * 2.5 + u_time * 0.9) * 0.05;

    pos.y = wave1 + wave2 + wave3 + wave4;

    
    float seed = fract(sin(pos.x * 123.45 + pos.z * 678.90) * 4567.8);
    float jitter = sin(u_time * 2.0 + seed * 6.2831) * 0.025; 
    pos.y += jitter;
    

    FragPosWorld = pos;

    gl_Position = projection * view * vec4(pos, 1.0);
    float dist = gl_Position.w;

    float perspectiveSize = ((180.0)/dist*0.3+0.3);
    
    gl_PointSize = clamp(perspectiveSize, 12.0, 30.0); 
}
