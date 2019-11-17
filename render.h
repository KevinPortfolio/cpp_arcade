#if !defined(RENDER_H)
#define RENDER_H

#define VERTEX_SHADER            0x8B31
#define FRAGMENT_SHADER          0x8B30

#define ARRAY_BUFFER	         0x8892
#define RENDER_DATA_TYPE_FLOAT   0x1406

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
};

extern "C" inline void
render_initialize_libraries();

extern "C" inline void
render_set_screen_clear_color(float32 color[4]);

extern "C" inline void
render_clear_screen();

inline void
render_set_viewport(int32 min_x, int32 min_y, int32 max_x, int32 max_y);

uint32
render_compile_shader(byte* source_code, uint32 type);

int32
render_link_shader(Shader *shader);

extern "C" inline void
render_delete_shader_disk_data(uint32 shader_id);

extern "C" inline void
render_use_shader(uint32 id_shader);

void
render_delete_shader(uint32 id_shader);

uint32
render_alloc_and_fill_buffer(void* data, uint32 buffer_byte_size, uint32 type);
  
void
render_create_object(RenderObject* render_object);

#endif
