#include <gl/gl.h>
#include "opengl.h"

inline void
render_initialize_libraries()
{
  opengl_load_functions();
}

inline void
render_set_screen_clear_color(float32 color[4])
{
  glClearColor(color[0], color[1], color[2], color[3]);
}

inline void
render_clear_screen()
{
  glClear(GL_COLOR_BUFFER_BIT);
}

inline void
render_set_viewport(int32 min_x, int32 min_y, int32 max_x, int32 max_y)
{
  glViewport(min_x, min_y, max_x, max_y);
}

uint32
render_compile_shader(byte* source_code, uint32 type)
{
  char error_buffer[256] = {};
  GLsizei error_length = 0;
  GLint error = glGetError();
  GLuint shader_id = glCreateShader(type);
  glShaderSource(shader_id, 1, (const char**)&source_code, 0);
  glCompileShader(shader_id);
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &error);
  if (error == GL_FALSE)
  {
    glGetShaderInfoLog(shader_id, 256, &error_length, error_buffer);
    glDeleteShader(shader_id);
  }

  if (error != GL_NO_ERROR)
  {
    // TODO: Handle error
  }

  return shader_id;
}

int32
render_link_shader(Shader *shader)
{
  char error_buffer[256] = {};
  GLsizei error_length = 0;
  shader->id = glCreateProgram();
  GLint error = 0;

  for (int component_index = 0;
       component_index < (sizeof(shader->shader_component)/sizeof(uint32));
       component_index++)
  {
      glAttachShader(shader->id, shader->shader_component[component_index]);
      glGetProgramiv(shader->id, GL_ATTACHED_SHADERS, &error);
      if (error == GL_FALSE)
	glGetShaderInfoLog(shader->id, 256, &error_length, error_buffer);
  }
  
  glLinkProgram(shader->id);
  glGetProgramiv(shader->id, GL_LINK_STATUS, &error);
  if (error == GL_FALSE)
    glGetProgramInfoLog(shader->id, 256, &error_length, error_buffer);
  
  error = glGetError();

  for (int component_index = 0;
       component_index < (sizeof(shader->shader_component)/sizeof(uint32));
       component_index++)
    glDetachShader(shader->id, shader->shader_component[component_index]);

  return error;
}

inline void
render_delete_shader_disk_data(uint32 shader_id)
{
  glDeleteShader(shader_id);
}
