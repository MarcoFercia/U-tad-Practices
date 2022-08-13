#version 420

uniform mat4 mvp;
uniform mat4 mv;
uniform mat4 nmatrix;
uniform int numLights;


struct lightstruct
{
vec4 ambient;
vec4 diffuse;
vec4 specular;
vec3 position;
int boolPointLight;
float linearAttenuation;
};

 uniform lightstruct lights[2];


in vec3 vpos;
in vec3 vnormal;
in vec2 vtex;



out vec2 _tex;
out vec3 N[2];
out vec3 L[2];
out vec3 H[2];
out vec4 _pos;

out lightstruct _lights[2];


void main() 
{

vec4 point = mv * vec4(vnormal, 1.0);

    for(int i = 0; i < numLights;++i)
    {
       N[i] = normalize((nmatrix * vec4(vnormal, 1.0)).xyz);
       L[i] = lights[i].position - point.xyz;
       H[i] = normalize(L[i]) - point.xyz;
    }


    gl_Position = mvp * vec4(vpos, 1);
    _tex = vtex;
    _pos = point;
    _lights = lights;
  
}