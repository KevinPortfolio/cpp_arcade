
int32
program_start_up(GameState* game_state)
{
  float blue[4] = {0.0f, 0.0f, 1.0f, 0.0};
  render_set_screen_clear_color(blue);
  render_set_viewport(0, 0, game_state->window_width, game_state->window_height);

  File shader_file = platform_read_file("default.shader");
  //byte* vertice_shader_source = parse_glsl_vertice(shader_file.data, shader_file.byte_size);
  //byte* fragment_shader_source = parse_glsl_fragment(shader_file.data, shader_file.byte_size);
  //Shader shader = render_compile_shader(vertice_shader_source, fragment_shader_source);

  delete[] shader_file.data;
  render_clear_screen();
  return 1;
}

int32
program_run_loop()
{
  render_clear_screen();
  return 1;
}
