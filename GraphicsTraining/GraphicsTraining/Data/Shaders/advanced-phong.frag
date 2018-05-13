#version 330 core
out vec4 FragColor;

in VS_OUT
{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoord;
} fs_in;

uniform vec3 objectColor;
uniform sampler2D colorTexture;
uniform bool hasTexture;

uniform sampler2D normalMap;
uniform bool hasNormalMap;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform vec3 viewPos;

uniform bool blinn;


void main()
{
	vec3 color = hasTexture ? texture(colorTexture, fs_in.TexCoord).rgb : objectColor;
    // ambient
    float ambientStrength = 0.05;
    vec3 ambient = ambientStrength * color;

    // diffuse
    vec3 norm = normalize(hasNormalMap ? texture(normalMap, fs_in.TexCoord).rgb : fs_in.Normal);
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float diff = max(dot(lightDir, norm), 0.0);
    vec3 diffuse = diff * color;

    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    float spec = 0.0;

	if(blinn)
	{
		vec3 halfwayDir = normalize(lightDir + viewDir);
		spec = pow(max(dot(norm, halfwayDir), 0.0), 32);
	}
	else
	{
    	vec3 reflectDir = reflect(-lightDir, norm);
		spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
	}

    vec3 specular = spec * lightColor;

    vec3 result = (ambient + diffuse + specular);
    FragColor = vec4(result, 1.0);
}
