#include <gl/gl.h>
#include "opengl.h"

inline void
render_initialize_libraries()
{
  opengl_load_functions();
  glLineWidth(10.0f);
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

  for (int32 component_index = 0;
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

inline void
render_use_shader(uint32 id_shader)
{
  glUseProgram(id_shader);
}

inline void
render_delete_shader(uint32 id_shader)
{
  glUseProgram(0);
  glDeleteProgram(id_shader);
}

uint32
render_alloc_and_fill_buffer(void* data, uint32 buffer_byte_size, uint32 type)
{
  uint32 buffer_id;
  glGenBuffers(1, &buffer_id);
  glBindBuffer(type, buffer_id);
  glBufferData(type, buffer_byte_size, data, GL_STATIC_DRAW);
  glBindBuffer(type, 0);
  // TODO: Error handling
  return buffer_id;
}

void
render_create_object(RenderObject* render_object)
{
  glGenVertexArrays(1, &render_object->id);	
  glBindVertexArray(render_object->id);

  for (uint32 element_index = 0; element_index < render_object->element_count; element_index++)
  {
    glBindBuffer(GL_ARRAY_BUFFER, render_object->element[element_index].id);
    glVertexAttribPointer(element_index, render_object->element[element_index].count_per_subset,
			  render_object->element[element_index].data_type, GL_FALSE,
			  render_object->element[element_index].bytes_per_subset, 0);
    glEnableVertexAttribArray(element_index);
  }
  glBindVertexArray(0);
}

void
render_draw(unsigned int render_object_id, int start_vertex, unsigned int vertice_count, int mode)
{
  glBindVertexArray(render_object_id);
  glDrawArrays(mode, start_vertex, vertice_count);
  glBindVertexArray(0);
}

inline void
render_update_mat4x4(unsigned int variable_position, float* data)
{
  glUniformMatrix4fv(variable_position, 1, 0, data);
}
