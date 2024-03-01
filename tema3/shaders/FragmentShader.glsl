#version 330
// Input
in vec2 texcoord;
in float ramas;
in float misca;
in vec3 world_position;
in vec3 world_normal;

// Uniform
uniform sampler2D texture_1;
uniform sampler2D texture_2;

uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform float unghi_cut_off[2];

//Output
layout(location = 0) out vec4 out_color;

void main(){
	
	vec4 color1 = texture2D(texture_1,texcoord);
	vec4 color2 = texture2D(texture_2,texcoord);
	vec2 modulated_coords = (vec2(sin(world_position.x * 30)) + 1) * 0.008f;
	if(misca == 1) {
		color1 = texture2D(texture_1, texcoord + ramas/13 + modulated_coords);
		color2 = texture2D(texture_2, texcoord + ramas/13 + modulated_coords);
	}
	vec4 color = mix(color1,color2,0.5f);
	if(color.a < 0.5){
		discard;
	}
	out_color = color;
}