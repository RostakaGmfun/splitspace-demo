layout (location=INPUT_VPOS) in vec3 inPosition;
layout (location=INPUT_VTEX) in vec2 inTexcoord;
layout (location=INPUT_VNORM) in vec3 inNormal;

out vec3 WorldPos;
out vec3 WorldNormal;
out vec2 Texcoord;

uniform mat4 MVP;
uniform mat4 WorldMat;

void main() {
    WorldPos = vec3(WorldMat * vec4(inPosition, 1.0));
    WorldNormal = vec3(WorldMat * vec4(inNormal, 1.0));
    Texcoord = inTexcoord;
    gl_Position = MVP * vec4(inPosition, 1.0);
}

