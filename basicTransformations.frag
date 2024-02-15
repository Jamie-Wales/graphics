#version 430

in  vec3 ex_Color;  //colour arriving from the vertex
in vec2 TexCoord;
out vec4 out_Color; //colour for the pixel

uniform sampler2D ourTexture;

void main(void)
{
	out_Color = texture(ourTexture, TexCoord) * vec4(ex_Color, 1.0);

}