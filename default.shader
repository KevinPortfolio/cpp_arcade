@vertex@
#version 430 core

layout(location = 0) in vec3 PositionData;
layout(location = 1) in vec3 ColorData;

layout(location = 5) uniform mat4 model;
layout(location = 6) uniform mat4 view;
layout(location = 7) uniform mat4 projection;

out vec3 Color;
out vec3 FragPos;

void main(void)
{
	FragPos = vec3(model * vec4(PositionData, 1.0));
	gl_Position = projection * view * vec4(FragPos, 1.0);
	Color = ColorData;
}
@stop@
@fragment@
#version 430 core

in vec3 FragPos;
in vec3 Color;

out vec4 FragColor;

void main(void)
{
	FragColor = vec4(Color, 1.0);
}
@stop@