#version 330 core

in vec3 vertColor;

out vec4 fragColor;

uniform float iTime;
uniform uvec2 iResolution;

void main() {
	vec3 col = 0.5 + 0.5 * cos( iTime + vec3(2,4,6) );
	col = mix( col, vertColor, 0.5 );
	col = vertColor;
	fragColor = vec4( col, 1.0 );
}
