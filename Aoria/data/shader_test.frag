#version 120
uniform float time;

vec3 colorB = vec3(0.1,0.1,0.2);
vec3 colorA = vec3(0.0,0.0,0.001);

void main() {
    vec3 color = vec3(0.0);

    float pct = abs(cos(time)) * 0.9;

    color = mix(colorA, colorB, pct);

    gl_FragColor = vec4(color,1.0);
}