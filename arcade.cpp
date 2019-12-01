static Camera camera;
static RenderObject line;
static RenderObject rectangle;

static RenderIteration rect;

static Shader shader[3];
static Font font_a;
static uint32 white_texture_id;

typedef void
module(GameState* game_state);

static module *modules[4];

int32
program_start_up(GameState* game_state)
{
  modules[0] = (module*)load_menu;
  modules[1] = (module*)menu_loop;
  modules[2] = (module*)load_block_fall;
  modules[3] = (module*)block_fall_loop;
  
  platform_create_font("c:/Windows/Fonts/arial.ttf\0", "arial\0", &font_a, 24, FONT_NORMAL);
  console_start_position = v3(0.0f, game_state->window_height - font_a.height, 0.0f);
  console_caret = console_start_position;
  
  render_initialize_libraries();
  render_enable(RENDER_BLEND);
  render_set_blend_func(RENDER_SOURCE_ALPHA, RENDER_BLEND_FUNC_ONE_MINUS_SRC_ALPHA);
  
  temp_create_shader(&shader[0], "../../repo/cpp_arcade/default.shader");
  temp_create_shader(&shader[1], "../../repo/cpp_arcade/default_texture.shader");
  temp_create_shader(&shader[2], "../../repo/cpp_arcade/text.shader");

  gpu_alloc_font(&font_a);
  
  float32 clear_screen_color[4] = {0.0f, 0.0f, 0.0f, 0.0};
  render_set_screen_clear_color(clear_screen_color);
  render_set_viewport(0, 0, game_state->window_width, game_state->window_height);
  
  camera.up_vec = v3(0.0f, 1.0f, 0.0f);
  camera.forward_vec = v3(0.0f, 0.0f, -1.0f);
  camera.position = v3(0.0f, 0.0f, 1.0f);
  camera.projection_mat = math_ortho_mat(0.0f,
		    (float32)game_state->window_width, 0.0f,
		    (float32)game_state->window_height, 0.1f, 1000.0f, 1);
 
  v3 updated_forward_vec = camera.position + camera.forward_vec;
  camera.view_mat = math_lookat_mat(camera.position, updated_forward_vec, camera.up_vec);

  byte white_texture_data[4] = {0xFF, 0xFF, 0xFF, 0xFF};
  render_allocate_texture(&white_texture_id, white_texture_data, 1, 1, 4);
  
  v3 point_a(game_state->window_width / 2.0f, 100.0f, 0.0f);
  v3 point_b(game_state->window_width / 2.0f, game_state->window_height - 100.0f, 0.0f);
 
  gpu_alloc_line(&line, point_a, point_b);
  
  game_state->camera = &camera;
  game_state->texture_id = white_texture_id;
  game_state->shader_id = shader[1].id;
  game_state->text_shader_id = shader[2].id;
  game_state->font = &font_a;
  
  platform_delete_font(&font_a);
  render_clear_screen();
  
  game_state->module_id = 0;
  return 1;
}
  
int32
program_run_loop(GameState *game_state)
{
  render_clear_screen();
  
  modules[game_state->module_id](game_state);
    
  render_use_shader(shader[2].id);  // NOTE: begin console draw
  render_update_mat4x4(3, camera.view_mat.arr);
  render_update_mat4x4(4, camera.projection_mat.arr);
  render_update_int(5, 0);
  v3 red(0.0f, 1.0f, 0.0f);
  render_update_vec3(6, red.arr);
    
  temp_text_print_line(font_a, "Hello World!");
  temp_text_print_line(font_a, "Is this thing working?");
  console_caret = console_start_position;
  return 1;
}
