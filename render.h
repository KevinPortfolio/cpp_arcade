#if !defined(RENDER_H)
#define RENDER_H

#define VERTEX_SHADER            0x8B31
#define FRAGMENT_SHADER          0x8B30

#define ARRAY_BUFFER	         0x8892
#define RENDER_DATA_TYPE_FLOAT   0x1406

#define RENDER_MODE_POINTS          0x0000
#define RENDER_MODE_LINES           0x0001
#define RENDER_MODE_LINE_LOOP       0x0002
#define RENDER_MODE_LINE_STRIP      0x0003
#define RENDER_MODE_TRIANGLES       0x0004
#define RENDER_MODE_TRIANGLE_STRIP  0x0005
#define RENDER_MODE_TRIANGLE_FAN    0x0006
#define RENDER_MODE_QUADS           0x0007
#define RENDER_MODE_QUAD_STRIP      0x0008
#define RENDER_MODE_POLYGON         0x0009

struct Shader
{
  union
  {
    struct
    {
      uint32 vertex;
      uint32 fragment;
    };
    uint32 shader_component[2];
  };
  uint32 id;
};

struct RenderElement
{
  uint32 id;
  uint32 bytes_per_subset;
  uint32 count_per_subset;
  int32 data_type;
};

struct RenderObject
{
  RenderElement element[3];
  uint32 id;
  uint32 element_count;
  uint32 vertice_count;
};

extern "C" inline void
render_initialize_libraries();

extern "C" inline void
render_set_screen_clear_color(float32 color[4]);

extern "C" inline void
render_clear_screen();

extern "C" inline void
render_set_viewport(int32 min_x, int32 min_y, int32 max_x, int32 max_y);

uint32
render_compile_shader(byte* source_code, uint32 type);

int32
render_link_shader(Shader *shader);

extern "C" inline void
render_delete_shader_disk_data(uint32 shader_id);

extern "C" inline void
render_use_shader(uint32 id_shader);

extern "C" inline void
render_delete_shader(uint32 id_shader);

uint32
render_alloc_and_fill_buffer(void* data, uint32 buffer_byte_size, uint32 type);
  
void
render_create_object(RenderObject* render_object);

void
render_draw(unsigned int render_object_id, int start_vertex, unsigned int vertice_count, int mode);

extern "C" inline void
render_update_mat4x4(unsigned int variable_position, float* data);

#endif
