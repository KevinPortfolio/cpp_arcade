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
  float32 *vertice;
  float32 *color;
  float32 *texture_coord;
  uint32 *indice;
  uint32 vertice_arr_size;
  uint32 color_arr_size;
  uint32 texture_coord_arr_size;
  uint32 indice_arr_size;
};

struct Font
{
  char* name;
  int32 height;
  int32 weight;
  int32 glyph_width[95]{};
  int32 glyph_height[95]{};
  byte* glyph_data[95]{};
  uint32 texture_id[95]{};
};

Shader
parse_glsl(byte* shader_file_data, uint32 byte_count);

#endif
