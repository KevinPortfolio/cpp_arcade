#if !defined(ARCADE_H)
#define ARCADE_H

struct GameState
{
  int32 window_width;
  int32 window_height;
};

struct File
{
  byte* data;
  uint32 byte_size;
};
#endif