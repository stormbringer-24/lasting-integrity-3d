#version 410 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform sampler2D diffuseMap;

void main() {
    vec2 fixedUV = TexCoords;
    if (abs(Normal.y) < 0.1) {
        fixedUV.y *= 7.5; 
    }

    vec3 baseColor = texture(diffuseMap, fixedUV).rgb * 0.8; 

    vec3 lightPos = vec3(10.0, 10.0, -30.0); 
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 norm = normalize(Normal);

    vec3 ambient = vec3(0.4, 0.4, 0.5); 
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(0.6, 0.6, 0.7); 

    vec3 resultColor = (ambient + diffuse) * baseColor;
    vec3 fogColor = vec3(0.04, 0.02, 0.08);
    float heightFog = clamp(1.0 - (FragPos.y + 2.0) / 3.0, 0.0, 1.0);
    vec3 finalColor = mix(resultColor, fogColor, heightFog * 0.35);

    FragColor = vec4(finalColor, 1.0);
}
