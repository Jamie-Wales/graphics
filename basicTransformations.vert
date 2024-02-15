#version 430

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

in  vec3 in_Position;  // Position coming in
in  vec3 in_Color;     // colour coming in
in vec2 aTexCoord;
out vec3 ex_Color;     // colour leaving the vertex, this will be sent to the fragment shader
out vec2 TexCoord;

void main(void)
{
	gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(in_Position, 1.0);
	ex_Color = in_Color;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}