#version 410 core
in vec3 FragPosWorld;
out vec4 FragColor;
uniform vec3 viewPos;

void main() {
    vec2 coord = gl_PointCoord * 2.0 - vec2(1.0);
    float distsq = dot(coord, coord);
    if(distsq > 1.00) discard;
    
    float z = sqrt(1.0 - distsq);
    vec3 normal = normalize(vec3(coord.x, coord.y, z));
    vec3 viewdir = normalize(viewPos - FragPosWorld);

    vec3 lightdir1 = normalize(vec3(0.5, 1.0, 0.8));
    float diff1 = max(dot(normal, lightdir1), 0.0);
    vec3 halftdir1 = normalize(lightdir1 + viewdir);
    float spec1 = pow(max(dot(normal, halftdir1), 0.0), 128.0); 

    vec3 lightPos_back = vec3(0.0, 20.0, -200.0); 
    vec3 lightdir2 = normalize(lightPos_back - FragPosWorld);
    float dist_back = length(lightPos_back - FragPosWorld);
    float diff2 = max(dot(normal, lightdir2), 0.0);
    
    float attenuation = 1.0 / (1.0 + 0.00005 * dist_back);
    diff2 *= attenuation;

    float fresnel = pow(1.0 - max(dot(normal, viewdir), 0.0), 3.0);

    vec3 basecolor = vec3(0.065, 0.05, 0.07); 
    vec3 highlight = vec3(0.9, 0.95, 1.0);  
    vec3 fresnelcolor = vec3(0.1, 0.3, 0.6); 

    float distancecam = length(viewPos - FragPosWorld);

    vec3 finalcolor = basecolor * (diff1 + (diff2 * 3.0) + 1.25); 

    float horizonFactor = smoothstep(40.0, 200.0, distancecam);

    vec3 horizonLight = vec3(0.25, 0.28, 0.38); 
    
    finalcolor += horizonLight * horizonFactor * (fresnel + 0.2); 

    finalcolor += (highlight * spec1 * 0.5 );
    finalcolor += (fresnelcolor * fresnel * 0.8);
    
    finalcolor *= smoothstep(1.0, 0.5, sqrt(distsq)); 


   float fogStart = 30.0;
float fogEnd = 120.0;
float fogFactor = smoothstep(fogStart, fogEnd, distancecam);
vec3 fogColor = vec3(0.08, 0.03, 0.12); // dark purple fog color
finalcolor = mix(finalcolor, fogColor, fogFactor);

FragColor = vec4(finalcolor, 1.0);

}
