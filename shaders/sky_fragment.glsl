#version 410 core
out vec4 FragColor;

in vec2 TexCoords;

uniform float u_time;
uniform sampler2D cloudMap;

void main() {
    vec2 uv = TexCoords * 2.0 - 1.0;
    uv.x *= 1.777; 

    vec2 sunPos = vec2(1.0, 0.5); 
    float dist = length(uv - sunPos);
    float sunRadius = 0.12;
    float sunMask = smoothstep(sunRadius - 0.005, sunRadius, dist);

    vec3 skyBottom = vec3(0.01, 0.0, 0.03);
    vec3 skyTop= vec3(0.12, 0.02, 0.18);
    vec3 baseSky = mix(skyBottom, skyTop, TexCoords.y);

    float innerCorona = exp(-20.0 * max(0.0, dist - sunRadius));
    float outerCorona = exp(-6.0 * max(0.0, dist - sunRadius));
    float shimmer = 1.0 + 0.15 * sin(u_time * 1.0 + dist * 40.0);

    vec3 coronaInner = vec3(0.9, 0.95, 1.0) * innerCorona * 1.0;
    vec3 coronaOuter = vec3(0.4, 0.55, 1.0) * outerCorona * 0.2 * shimmer;
    vec3 coronaColor = coronaInner + coronaOuter;

    vec3 skyWithEclipse = mix(vec3(0.0), baseSky + coronaColor, sunMask);

    vec2 uv1 = TexCoords * 1.5; uv1.x += u_time * 0.01;
    float cloud1 = texture(cloudMap, uv1).r;

    vec2 uv2 = TexCoords * 3.5 + vec2(0.37, 0.61);
    uv2.x += u_time * 0.025; uv2.y += u_time * 0.005;

    vec2 uv3 = TexCoords * 7.0 + vec2(0.71, 0.23);
    uv3.x += u_time * 0.045;
    float cloud2 = texture(cloudMap, uv2).r;
    float cloud3 = texture(cloudMap, uv3).r;

    float finalCloudNoise = cloud1 * 0.5 + cloud2 * 0.35 + cloud3 * 0.15;
    finalCloudNoise = smoothstep(0.35, 0.85, finalCloudNoise);
    float horizonMask = smoothstep(0.15, 0.65, TexCoords.y);
    finalCloudNoise *= horizonMask;

    vec3 cloudColor = vec3(0.25, 0.15, 0.35); 
    vec3 finalColor = mix(skyWithEclipse, cloudColor, finalCloudNoise * 0.85);

    const int NUM_SAMPLES = 6; 
    float stepSize = 0.07; 

    vec2 rayDir = (sunPos - uv);
    vec2 sampleUV = uv;
    float godRayAccum = 0.0;

    vec2 timeOffset = vec2(u_time * 0.015, u_time * 0.005);

    for (int i = 0; i < NUM_SAMPLES; i++) {
        sampleUV += rayDir * stepSize;
        
        vec2 sampleTC = (sampleUV / vec2(1.777, 1.0) + 1.0) * 0.5;

        float cloudDensity = texture(cloudMap, sampleTC * 2.0 + timeOffset).r;
        cloudDensity = smoothstep(0.4, 0.9, cloudDensity);

        float sampleDist = length(sampleUV - sunPos);
        float lightAtThisPoint = exp(-8.0 * max(0.0, sampleDist - sunRadius));

        godRayAccum += lightAtThisPoint * (1.0 - cloudDensity * 0.7);
    }

    godRayAccum /= float(NUM_SAMPLES);

    float distFalloff = exp(-3.0 * max(0.0, dist - sunRadius * 2.0));
    godRayAccum *= distFalloff;

    vec3 godRayColor = vec3(0.5, 0.65, 1.0) * godRayAccum * 0.35;

    godRayColor *= sunMask;

    finalColor += godRayColor;
    vec2 towerScreenPos = vec2(0.38, 0.28);
    float towerDist = length(TexCoords - towerScreenPos);
    float towerGlow = exp(-8.0 * towerDist) * 0.15;
    vec3 towerGlowColor = vec3(0.3, 0.45, 0.7);
    finalColor += towerGlowColor * towerGlow;

    FragColor = vec4(finalColor, 1.0);
}
