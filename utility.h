#if !defined(UTILITY_H)
#define UTILITY_H

struct Rect
{
  v3 bottom_left;
  v3 top_right;
};

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
  float32 *vertice;
  float32 *color;
  float32 *texture_coord;
  uint32 *indice;
  uint32 vertice_arr_size;
  uint32 color_arr_size;
  uint32 texture_coord_arr_size;
  uint32 indice_arr_size;
};

struct RenderIteration
{
  RenderObject* render_object;
  v3* position;
  uint32 shader_id;
  uint32 render_count;
};

Shader
parse_glsl(byte* shader_file_data, uint32 byte_count);

#endif
