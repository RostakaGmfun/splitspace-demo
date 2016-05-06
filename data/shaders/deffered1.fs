in vec3 WorldPos;
in vec3 WorldNormal;
in vec2 Texcoord;


out vec3 _OUT0; // position (world)
out vec3 _OUT1; // normal (world)
out vec3 _OUT2; // color

uniform sampler2D diffuseMap;
uniform LightInfo lights[MAX_LIGHTS];
uniform int numLights;
uniform Material material;

void main() {
    _OUT0 = WorldPos;
    _OUT1 = normalize(WorldNormal);
    _OUT2 = vec3(splitspace_Material(material, diffuseMap, Texcoord));
}
