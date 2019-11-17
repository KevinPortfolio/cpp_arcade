#if !defined(UTILITY_H)
#define UTILITY_H

struct Camera
{
  v3 up_vec;
  v3 forward_vec;
  v3 position;
  m4 projection_mat;
  m4 view_mat;
};

Shader
parse_glsl(byte* shader_file_data, uint32 byte_count);

#endif
