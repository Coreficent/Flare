#version 400

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;
uniform sampler2D imageSampler;

void main()
{
	vec4 textureColor = texture(imageSampler, fragmentUV);
	color = textureColor * fragmentColor;
}
