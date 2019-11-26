#if !defined(ARCADE_H)
#define ARCADE_H

struct GameState
{
  Camera *camera;
  int32 window_width;
  int32 window_height;
  uint32 module_id;
  uint32 shader_id;
  uint32 texture_id;
};

struct File
{
  byte* data;
  uint32 byte_size;
};
#endif
