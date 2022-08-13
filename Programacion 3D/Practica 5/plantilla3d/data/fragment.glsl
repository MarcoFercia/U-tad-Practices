
uniform sampler2D texSampler;
uniform int _numLights;
uniform vec3 _globalAmbient;

struct MaterialProperties
{
vec4 ambient;
vec4 diffuse;
vec4 specular;
float shininess;
};

uniform MaterialProperties mat;


struct lightstruct
{
vec4 ambient;
vec4 diffuse;
vec4 specular;
vec3 position;
int boolPointLight;
float linearAttenuation;
};

 in lightstruct _lights[2];

in vec2 _tex;
in vec4 _pos;
in vec3 N[2];
in vec3 L[2];
in vec3 H[2];


void main() 
{
	vec3 ambient = vec3(0,0,0);
	vec3 diffuse = _globalAmbient;
	vec3 specular = vec3(0,0,0);

	for(int j = 0; j < _numLights;++j)
	{
		vec3 tempL = L[j];
		float attenuation = 1.0;

		if(_lights[j].boolPointLight  > 0 )
		{			
			float distance = length(tempL);			
			attenuation = 1.f/(1.f + _lights[j].linearAttenuation * distance);			
		}

		tempL = normalize(tempL);
		diffuse = diffuse + _lights[j].diffuse.xyz * mat.diffuse.xyz * max(dot(tempL, N[j]), 0.0);
		diffuse = diffuse * attenuation;
		specular = specular + mat.specular.xyz * _lights[j].specular.xyz * pow(max(dot(H[j], N[j]),0.0),mat.shininess);
		specular = specular * attenuation;
	}

	ambient = ambient + (_globalAmbient * vec3(mat.ambient.x, mat.ambient.y, mat.ambient.z));

	vec4 resultLight = vec4((ambient + diffuse + specular),1.0);
	gl_FragColor = texture2D(texSampler, _tex) * resultLight;
}