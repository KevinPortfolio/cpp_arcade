
int32
program_start_up(GameState* game_state)
{
  render_initialize_libraries();
  
  float blue[4] = {0.0f, 0.0f, 1.0f, 0.0};
  render_set_screen_clear_color(blue);
  render_set_viewport(0, 0, game_state->window_width, game_state->window_height);

  File shader_file = platform_read_file("../../repo/cpp_arcade/default.shader");
  File vertice_shader_source = parse_glsl_vertice(shader_file);
  File fragment_shader_source = parse_glsl_fragment(shader_file);
  
  Shader shader;
  shader.vertex = render_compile_shader(vertice_shader_source.data, VERTEX_SHADER);
  shader.fragment = render_compile_shader(fragment_shader_source.data, FRAGMENT_SHADER);
  int error = render_link_shader(&shader);
  // NOTE: Still need to delete shader program
  if (vertice_shader_source.data)
  {
    render_delete_shader_disk_data(shader.vertex);
    delete[] vertice_shader_source.data;
  }
  if (fragment_shader_source.data)
  {
    render_delete_shader_disk_data(shader.fragment);
    delete[] fragment_shader_source.data;
  }
  if (shader_file.data)
    delete[] shader_file.data;
 
  /*
  Camera camera;
  camera.up_vector = v3(0.0f, 1.0f, 0.0f);
  camera.forward_vector = v3(0.0f, 0.0f, -1.0f);
  camera.position = v3(0.0f, 0.0f, 0.0f);
  camera.projection_matrix =
    math_perspective_mat(45.0f, (float)(game_state->window_width) /
			 (float)(game_state->window_height), 0.1f, 1000000.0f);
  */

  
  render_clear_screen();
  return 1;
}

int32
program_run_loop()
{
  render_clear_screen();
  return 1;
}
