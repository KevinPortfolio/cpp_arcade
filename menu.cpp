
RenderObject button;
RenderIteration buttons;
CollidableRect a, b;

void
load_menu(GameState *game_state)
{
  gpu_alloc_rectangle(&button, 100.0f, 50.f);

  buttons.render_object = &button;
  buttons.render_count = 2;
  buttons.position = new v3[buttons.render_count]{};
  buttons.shader_id = game_state->shader_id;
  buttons.position[0] = v3(500.0f, 500.0f, 0.0f);
  buttons.position[1] = v3(100.0f, 500.0f, 0.0f);

  a.min = v3(100.0f, 500.0f, 0.0f);
  a.max = v3(200.0f, 550.0f, 0.0f);

  b.min = v3(500.0f, 500.0f, 0.0f);
  b.max = v3(600.0f, 550.0f, 0.0f);

  game_state->module_id = 1;
}

void
menu_loop(GameState *game_state)
{
  render_use_shader(buttons.shader_id);
  render_update_mat4x4(3, game_state->camera->view_mat.arr);
  render_update_mat4x4(4, game_state->camera->projection_mat.arr);
  //  render_update_int(5, 0);

  float64 cursor_x;
  float64 cursor_y;
  platform_get_cursor_position(&cursor_x, &cursor_y);
  v3 cursor_position((float32)cursor_x, -((float32)cursor_y - (float32)game_state->window_height), 0.0f);

  //  v3 cursor_ray = collision_screen_picking(&game_state->camera->projection_mat, &game_state->camera->view_mat,
  //					   &cursor_position, game_state->window_width, game_state->window_height);

  if (collision_test(cursor_position, a) && (game_state->mouse.left_down == 1))
  {
    game_state->module_id = 2;
  }
  if (collision_test(a, b))
  {
    game_state->module_id = 2;
  }
  else
  {
    //buttons.position[1].x += 0.1f;
    //a.min.x += 0.1f;
    //a.max.x += 0.1f;
  }
  
  render_bind_texture(game_state->texture_id);
  draw_render_iteration(&buttons);
  render_bind_texture(0);
}
