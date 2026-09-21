#version 410 core
out vec4 FragColor;

in float vBrightness;
in vec3 vColor;

void main() {
   
    vec2 coord = gl_PointCoord * 2.0 - 1.0;
    float dist = length(coord);
    if (dist > 1.0) discard;
    float glow = exp(-3.5 * dist * dist);
    float halo = exp(-1.2 * dist * dist) * 0.4;
    float alpha = (glow + halo) * vBrightness;
    FragColor = vec4(vColor * vBrightness, alpha);
}