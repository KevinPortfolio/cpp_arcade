
static Camera camera;
static RenderObject line;

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

  render_use_shader(shader.id);
  camera.up_vec = v3(0.0f, 1.0f, 0.0f);
  camera.forward_vec = v3(0.0f, 0.0f, -1.0f);
  camera.position = v3(0.0f, 0.0f, 1.0f);
  camera.projection_mat = math_ortho_mat(0.0f, (float)game_state->window_width, 0.0f,
					  (float)game_state->window_height, 0.1f, 1000.0f, 1);
 
  v3 updated_forward_vec = camera.position + camera.forward_vec;
  camera.view_mat = math_lookat_mat(camera.position, updated_forward_vec, camera.up_vec);

  v3 point_a(game_state->window_width / 2.0f, 100.0f, 0.0f);
  v3 point_b(game_state->window_width / 2.0f, game_state->window_height - 100.0f, 0.0f);
  float line_vertice[6] =
    {
     point_a.x, point_a.y, point_a.z,
     point_b.x, point_b.y, point_b.z
    };
  
  float vertice_color[6] =
    {
     1.0f, 1.0f, 1.0f,
     1.0f, 1.0f, 1.0f
    };

  line.vertice_count = 6;
  line.element[0].id = render_alloc_and_fill_buffer(line_vertice, line.vertice_count * sizeof(float),
						    ARRAY_BUFFER);
  line.element[1].id = render_alloc_and_fill_buffer(vertice_color, line.vertice_count * sizeof(float),
						    ARRAY_BUFFER);
  line.element_count = 2;

  line.element[0].count_per_subset = 3;
  line.element[0].bytes_per_subset = line.element[0].count_per_subset * sizeof(float);
  line.element[0].data_type = RENDER_DATA_TYPE_FLOAT;
  line.element[1].count_per_subset = 3;
  line.element[1].bytes_per_subset = line.element[1].count_per_subset * sizeof(float);
  line.element[1].data_type = RENDER_DATA_TYPE_FLOAT; 
  
  render_create_object(&line);
  
  render_clear_screen();
  return 1;
}

int32
program_run_loop()
{
  render_clear_screen();
  
  render_update_mat4x4(3, camera.view_mat.arr);
  render_update_mat4x4(4, camera.projection_mat.arr);

  m4 identity_mat = math_identity_mat();
  render_update_mat4x4(2, identity_mat.arr);
  render_draw(line.id, 0, line.vertice_count, RENDER_MODE_LINES);
  return 1;
}
