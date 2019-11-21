@vertex@
#version 430 core

layout(location = 0) in vec3 PositionData;
layout(location = 1) in vec2 TextureCoord;

layout(location = 2) uniform mat4 model;
layout(location = 3) uniform mat4 view;
layout(location = 4) uniform mat4 projection;

out vec3 FragPos;
out vec2 TexCoord;

void main(void)
{
	FragPos = vec3(model * vec4(PositionData, 1.0));
	gl_Position = projection * view * vec4(FragPos, 1.0);
	TexCoord = TextureCoord;
}
@stop@
@fragment@
#version 430 core

layout(location = 5) uniform sampler2D TextureData;

in vec3 FragPos;
in vec2 TexCoord;

out vec4 FragColor;

void main(void)
{
	FragColor = texture(TextureData, TexCoord);
}
@stop@