#if !defined(ARCADE_H)
#define ARCADE_H

struct GameState
{
  Camera *camera;
  Font *font;
  Mouse mouse;
  
  int32 window_width;
  int32 window_height;
  uint32 module_id;
  uint32 shader_id;
  uint32 text_shader_id;
  uint32 texture_id;
};

#endif
