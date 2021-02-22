#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform float time;
uniform sampler2D cakeSampler;

void main() {
	
	vec4 textureColor = texture(cakeSampler, fragmentUV);
	
	//color = textureColor * fragmentColor;
	//color = textureColor;
	
    color = textureColor * vec4(fragmentColor.r * (cos(fragmentPosition.x * 4.0 + time) + 1.0) * 0.5, fragmentColor.g * (cos(fragmentPosition.y * 8.0 + time) + 1.0) * 0.5, fragmentColor.b * (cos(fragmentPosition.x * 2.0 + time) + 1.0) * 0.5, fragmentColor.a);
}