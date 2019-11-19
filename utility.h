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

struct ObjectMesh
{
  float *vertice;
  float *color;
  uint32 vertice_count;
};

Shader
parse_glsl(byte* shader_file_data, uint32 byte_count);

#endif
