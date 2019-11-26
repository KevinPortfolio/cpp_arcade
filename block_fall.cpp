
RenderObject game_rectangle;

RenderIteration game_rect;

void
load_block_fall(GameState* game_state)
{
  gpu_alloc_rectangle(&game_rectangle, 50.0f, 50.0f);

  game_rect.render_object = &game_rectangle;
  game_rect.render_count = 3;
  game_rect.position = new v3[game_rect.render_count]{};
  game_rect.shader_id = game_state->shader_id;
  game_rect.position[0] = v3(400.0f, 100.0f, 0.0);
  game_rect.position[1] = v3(200.0f, 100.0f, 0.0);
  game_rect.position[2] = v3(0.0f, 100.0f, 0.0);  
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
