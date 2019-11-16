#if !defined(RENDER_H)
#define RENDER_H

struct Shader
{
  uint32 vertice;
  uint32 fragment;
};

extern "C" inline void
render_set_screen_clear_color(float color[4]);

extern "C" inline void
render_clear_screen();

inline void
render_set_viewport(int min_x, int min_y, int max_x, int max_y);

#endif
