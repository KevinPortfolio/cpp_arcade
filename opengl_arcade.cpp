#include <gl/gl.h>

inline void
render_set_screen_clear_color(float color[4])
{
  glClearColor(color[0], color[1], color[2], color[3]);
}

inline void
render_clear_screen()
{
  glClear(GL_COLOR_BUFFER_BIT);
}

inline void
render_set_viewport(int min_x, int min_y, int max_x, int max_y)
{
  glViewport(min_x, min_y, max_x, max_y);
}
