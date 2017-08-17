#version 330 core

in vec2 textures;
in vec3 surface_normal;
in vec3 toLightVector;

out vec4 colour;

uniform sampler2D Texture_;
uniform vec3 light_colour;

void main( )
{

	vec3 unit_normal = normalize(surface_normal);
	vec3 unit_light_vect = normalize(toLightVector);

	float nDot1 = dot( unit_normal, unit_light_vect );
	float Brightness = max( nDot1, 0.0);
	vec3 diffuse = Brightness * light_colour;

	colour = vec4( diffuse, 1.0f)  * texture( Texture_ , textures );
};
