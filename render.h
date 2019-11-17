#if !defined(RENDER_H)
#define RENDER_H

#define VERTEX_SHADER   0x8B31
#define FRAGMENT_SHADER 0x8B30

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

inline void
render_delete_shader_disk_data(uint32 shader_id);

#endif
