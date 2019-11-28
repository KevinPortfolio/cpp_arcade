
static RenderObject game_rectangle;

static RenderIteration game_rect;

static v3 block_position[256]{};

void
load_block_fall(GameState* game_state)
{
  gpu_alloc_rectangle(&game_rectangle, 50.0f, 50.0f);

  game_rect.render_object = &game_rectangle;
  game_rect.render_count = 1;
  game_rect.position = new v3[game_rect.render_count]{};
  game_rect.shader_id = game_state->shader_id;

  game_state->module_id = 3;
}

void
block_fall_loop(GameState* game_state)
{
  render_use_shader(game_rect.shader_id);
  render_update_mat4x4(3, game_state->camera->view_mat.arr);
  render_update_mat4x4(4, game_state->camera->projection_mat.arr);
  render_update_int(5, 0);

  render_bind_texture(game_state->texture_id);
  draw_render_iteration(&game_rect);
  render_bind_texture(0);
}
