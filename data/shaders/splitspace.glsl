/*
 * Splitspace suppport file for GLSL shaders
 * Contains built-in engine definitions
 */

/*
 * Material definitions
 */
struct Material {
    vec3 ambient;
    vec4 diffuse;
    vec3 specular;
    bool isTextured;
    int technique;
};

/*
 * Rendering techinques
 */

#define RENDER_LAMBERT 1
#define RENDER_PHONG   2

vec4 splitspace_Material(Material material, sampler2D diffuseMap, vec2 uv) {
    if(material.isTextured) {
        return texture(diffuseMap, uv);
    } else {
        return material.diffuse;
    }
}


/*
 * Lighting definitions
 */

struct LightInfo {
    vec3 position;
    vec3 rotation;
    vec3 diffuse;
    vec3 specular;
    float spotLightCutoff;
    float power;
    vec3 attenuation;
    int type;
};

#define LIGHT_AMBIENT 1
#define LIGHT_SUN     2
#define LIGHT_POINT   3
#define LIGHT_SPOT    4

// Size of LightInfo array
#define MAX_LIGHTS    8

vec3 lambertLighting(vec3 vertex, vec3 normal, LightInfo light, vec3 inColor) {
    vec3 L = normalize(light.position-vertex);
    // TODO: add attenuation parameter to light
    // it should be vec3(constant, linear, qaudratic)
    float dist = distance(light.position, vertex);
    float attenuation = light.attenuation.x+dist*light.attenuation.y+
                        pow(dist,2)*light.attenuation.z;
    switch(light.type) {
        case LIGHT_AMBIENT:
            return inColor+light.diffuse;
        case LIGHT_SUN:
            return inColor+clamp(light.diffuse*max(dot(normal, light.rotation), 0.0),
                            0.0, 1.0)*light.power;
        case LIGHT_POINT:
            return inColor+
            clamp(light.diffuse*max(dot(normal, L), 0.0), 0.0, 1.0)*light.power*
            (1/attenuation);
        default:
            return inColor;
    }
}

vec3 phongLighting(vec3 vertex, vec3 normal, LightInfo light, Material material, vec3 inColor) {
    //TODO
    return vec3(0, 0, 0);
}

vec3 splitspace_Lighting(vec3 vertex, vec3 normal,
                               LightInfo light, Material material, vec3 inColor) {
    switch(material.technique) {
        case RENDER_LAMBERT:
            return lambertLighting(vertex, normal, light, inColor);
        case RENDER_PHONG:
            return phongLighting(vertex, normal, light, material, inColor);
        default:
            return vec3(0, 0, 0);
    }
}

/*
 * Locations for VS inputs
 */
#define INPUT_VPOS  0
#define INPUT_VTEX  1
#define INPUT_VNORM 2

