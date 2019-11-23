static Camera camera;
static RenderObject line;
static RenderObject rectangle;
static RenderObject glyph_render_obj[95]{};

static Shader shader[2];
static Font font;

void
temp_create_rectangle(RenderObject *rectangle, float width, float height)
{
  ObjectMesh rectangle_mesh;
  
  rectangle_mesh.vertice_arr_size = 12;
  rectangle_mesh.texture_coord_arr_size = 8;
  rectangle_mesh.indice_arr_size = 6;
  rectangle_mesh.texture_coord = new float32[rectangle_mesh.texture_coord_arr_size]
					    {0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };
  
  rectangle_mesh.indice = new uint32[rectangle_mesh.indice_arr_size] {0, 1, 3, 3, 2, 0};
  
  rectangle_mesh.vertice = new float32[rectangle_mesh.vertice_arr_size]
				      {0.0f, 0.0f, 0.0f, width,
				       0.0f, 0.0f, 0.0f, height, 0.0f,
				       width, height, 0.0f,};
    
  rectangle->vertice_count = 4;
  rectangle->indice_count = 6;
  rectangle->element[0].id = render_alloc_and_fill_buffer(rectangle_mesh.vertice,
	       rectangle_mesh.vertice_arr_size * sizeof(float32), ARRAY_BUFFER);
    
  rectangle->element[1].id = render_alloc_and_fill_buffer(rectangle_mesh.texture_coord,
	    rectangle_mesh.texture_coord_arr_size * sizeof(float32), ARRAY_BUFFER);
    
  rectangle->element[2].id = render_alloc_and_fill_buffer(rectangle_mesh.indice,
	    rectangle_mesh.indice_arr_size * sizeof(uint32), ELEMENT_ARRAY_BUFFER);
    
  rectangle->element_count = 2;
  rectangle->element[0].count_per_subset = 3;
  rectangle->element[0].bytes_per_subset = rectangle->element[0].count_per_subset * sizeof(float32);
  rectangle->element[0].data_type = RENDER_DATA_TYPE_FLOAT;
  
  rectangle->element[1].count_per_subset = 2;
  rectangle->element[1].bytes_per_subset = rectangle->element[1].count_per_subset * sizeof(float32);
  rectangle->element[1].data_type = RENDER_DATA_TYPE_FLOAT;
    
  rectangle->element[2].count_per_subset = 3;
  rectangle->element[2].bytes_per_subset = rectangle->element[1].count_per_subset * sizeof(uint32);
  rectangle->element[2].data_type = RENDER_DATA_TYPE_UNSIGNED_INT; 

  render_bind_buffer(rectangle->element[2].id, ELEMENT_ARRAY_BUFFER);
  render_create_object(rectangle);

  delete[] rectangle_mesh.vertice;
  delete[] rectangle_mesh.texture_coord;
  delete[] rectangle_mesh.indice;
}

void
temp_create_font_rectangles()
{
  ObjectMesh rectangle_mesh;

  rectangle_mesh.vertice_arr_size = 12;
  rectangle_mesh.texture_coord_arr_size = 8;
  rectangle_mesh.indice_arr_size = 6;
  rectangle_mesh.texture_coord =
    new float32[rectangle_mesh.texture_coord_arr_size]
		 {0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };
  
  rectangle_mesh.indice = new uint32[rectangle_mesh.indice_arr_size] {0, 1, 3, 3, 2, 0};
  
  for (int32 glyph_index = 0; glyph_index < 95; glyph_index++)
  {
    rectangle_mesh.vertice = new float32[rectangle_mesh.vertice_arr_size]
		       {0.0f, 0.0f, 0.0f, (float32)font.glyph_width[glyph_index],
			0.0f, 0.0f, 0.0f, (float32)font.glyph_height[glyph_index], 0.0f,
			(float32)font.glyph_width[glyph_index],
			(float32)font.glyph_height[glyph_index], 0.0f,};
    
    glyph_render_obj[glyph_index].vertice_count = 4;
    glyph_render_obj[glyph_index].indice_count = 6;
    glyph_render_obj[glyph_index].element[0].id =
      render_alloc_and_fill_buffer(rectangle_mesh.vertice,
	       rectangle_mesh.vertice_arr_size * sizeof(float32), ARRAY_BUFFER);
    
    glyph_render_obj[glyph_index].element[1].id =
      render_alloc_and_fill_buffer(rectangle_mesh.texture_coord,
	    rectangle_mesh.texture_coord_arr_size * sizeof(float32), ARRAY_BUFFER);
    
    glyph_render_obj[glyph_index].element[2].id =
      render_alloc_and_fill_buffer(rectangle_mesh.indice,
	    rectangle_mesh.indice_arr_size * sizeof(uint32), ELEMENT_ARRAY_BUFFER);
    
    delete[] rectangle_mesh.vertice;
    rectangle_mesh.vertice = 0;
    
    glyph_render_obj[glyph_index].element_count = 2;
    glyph_render_obj[glyph_index].element[0].count_per_subset = 3;
    glyph_render_obj[glyph_index].element[0].bytes_per_subset =
      glyph_render_obj[glyph_index].element[0].count_per_subset * sizeof(float32);
    glyph_render_obj[glyph_index].element[0].data_type = RENDER_DATA_TYPE_FLOAT;
    
    glyph_render_obj[glyph_index].element[1].count_per_subset = 2;
    glyph_render_obj[glyph_index].element[1].bytes_per_subset =
      glyph_render_obj[glyph_index].element[1].count_per_subset * sizeof(float32);
    glyph_render_obj[glyph_index].element[1].data_type = RENDER_DATA_TYPE_FLOAT;
    
    glyph_render_obj[glyph_index].element[2].count_per_subset = 3;
    glyph_render_obj[glyph_index].element[2].bytes_per_subset =
    glyph_render_obj[glyph_index].element[1].count_per_subset * sizeof(uint32);
    glyph_render_obj[glyph_index].element[2].data_type = RENDER_DATA_TYPE_UNSIGNED_INT; 

    render_bind_buffer(glyph_render_obj[glyph_index].element[2].id, ELEMENT_ARRAY_BUFFER);
    render_create_object(&glyph_render_obj[glyph_index]);

    render_allocate_texture(&font.texture_id[glyph_index], font.glyph_data[glyph_index],
		   font.glyph_width[glyph_index], font.glyph_height[glyph_index], 4);
    
  }
  delete[] rectangle_mesh.texture_coord;
  delete[] rectangle_mesh.indice;
}

void
temp_create_shader(Shader *shader, char* file_path)
{  
  File shader_file = platform_read_file(file_path);
  File vertice_shader_source = parse_glsl_vertice(shader_file);
  File fragment_shader_source = parse_glsl_fragment(shader_file);
  
  shader->vertex = render_compile_shader(vertice_shader_source.data, VERTEX_SHADER);
  shader->fragment = render_compile_shader(fragment_shader_source.data, FRAGMENT_SHADER);
  int error = render_link_shader(shader);

  // NOTE: Still need to delete shader program
  if (vertice_shader_source.data)
  {
    render_delete_shader_data(shader->vertex);
    delete[] vertice_shader_source.data;
    vertice_shader_source.data = 0;
    vertice_shader_source.byte_size = 0;
  }
  
  if (fragment_shader_source.data)
  {
    render_delete_shader_data(shader->fragment);
    delete[] fragment_shader_source.data;
    fragment_shader_source.data = 0;
    fragment_shader_source.byte_size = 0;
  }
  
  if (shader_file.data)
  {
    delete[] shader_file.data;
    shader_file.data = 0;
    shader_file.byte_size = 0;
  }
}

static v3 console_start_position(100.0f, 100.0f, 0.0f);
static v3 console_caret(100.0f, 100.0f, 0.0f);

void
temp_text_print_line(char* text)
{
  v3 rect_position = console_caret;
  m4 model_mat = math_identity_mat();
  model_mat = math_translate(model_mat, rect_position);
  render_update_mat4x4(2, model_mat.arr);

  while (*text)
  {
    char glyph = *(text++) - 32;
    render_bind_texture(font.texture_id[glyph]);
    render_draw(glyph_render_obj[glyph].id, glyph_render_obj[glyph].element[2].id,
		glyph_render_obj[glyph].indice_count);
    render_bind_texture(0);
    v3 new_rect_position(0.0f, 0.0f, 0.0f);
    new_rect_position.x += font.glyph_width[glyph];
    model_mat = math_translate(model_mat, new_rect_position);
    render_update_mat4x4(2, model_mat.arr);
  }
  console_caret.y -= font.height;
}

int32
program_start_up(GameState* game_state)
{
  platform_create_font("c:/Windows/Fonts/arial.ttf\0", "arial\0", &font, 24, FONT_NORMAL);
  render_initialize_libraries();
  temp_create_shader(&shader[0], "../../repo/cpp_arcade/default.shader");
  temp_create_shader(&shader[1], "../../repo/cpp_arcade/default_texture.shader");

  temp_create_font_rectangles();
  
  float32 blue[4] = {0.0f, 0.0f, 1.0f, 0.0};
  render_set_screen_clear_color(blue);
  render_set_viewport(0, 0, game_state->window_width, game_state->window_height);
  
  camera.up_vec = v3(0.0f, 1.0f, 0.0f);
  camera.forward_vec = v3(0.0f, 0.0f, -1.0f);
  camera.position = v3(0.0f, 0.0f, 1.0f);
  camera.projection_mat = math_ortho_mat(0.0f,
		    (float32)game_state->window_width, 0.0f,
		    (float32)game_state->window_height, 0.1f, 1000.0f, 1);
 
  v3 updated_forward_vec = camera.position + camera.forward_vec;
  camera.view_mat = math_lookat_mat(camera.position, updated_forward_vec, camera.up_vec);

  v3 point_a(game_state->window_width / 2.0f, 100.0f, 0.0f);
  v3 point_b(game_state->window_width / 2.0f, game_state->window_height - 100.0f, 0.0f);
 
  ObjectMesh line_mesh;
  line_mesh.vertice_arr_size = 6;
  line_mesh.color_arr_size = 6;
  
  line_mesh.vertice = new float32[line_mesh.vertice_arr_size] {
     point_a.x, point_a.y, point_a.z,
     point_b.x, point_b.y, point_b.z
    };  
  line_mesh.color = new float32[line_mesh.color_arr_size]{
     1.0f, 1.0f, 1.0f,
     1.0f, 1.0f, 1.0f
    };
  
  line.vertice_count = 2;
  line.element[0].id = render_alloc_and_fill_buffer(line_mesh.vertice,
			   line_mesh.vertice_arr_size * sizeof(float32), ARRAY_BUFFER);
  line.element[1].id = render_alloc_and_fill_buffer(line_mesh.color, 
                            line_mesh.color_arr_size * sizeof(float32), ARRAY_BUFFER);

  delete[] line_mesh.vertice;
  delete[] line_mesh.color;
  
  line.element_count = 2;
  line.element[0].count_per_subset = 3;
  line.element[0].bytes_per_subset = line.element[0].count_per_subset * sizeof(float32);
  line.element[0].data_type = RENDER_DATA_TYPE_FLOAT;
  line.element[1].count_per_subset = 3;
  line.element[1].bytes_per_subset = line.element[1].count_per_subset * sizeof(float32);
  line.element[1].data_type = RENDER_DATA_TYPE_FLOAT; 
  
  render_create_object(&line);  

  temp_create_rectangle(&rectangle, 100.0f, 100.0f);
  
  platform_delete_font(&font);
  render_clear_screen();
  return 1;
}

int32
program_run_loop()
{
  render_clear_screen();

  m4 model_mat = math_identity_mat();
  render_use_shader(shader[0].id);
  render_update_mat4x4(3, camera.view_mat.arr);
  render_update_mat4x4(4, camera.projection_mat.arr);
  render_update_mat4x4(2, model_mat.arr);

  render_draw(line.id, 0, line.vertice_count, RENDER_MODE_LINES);
    
  render_use_shader(shader[1].id);
  
  render_update_mat4x4(3, camera.view_mat.arr);
  render_update_mat4x4(4, camera.projection_mat.arr);
  render_update_int(5, 0);

  v3 position(200.0f, 200.0f, 0.0f);
  model_mat = math_translate(model_mat, position);
  render_update_mat4x4(2, model_mat.arr);
  render_draw(rectangle.id, rectangle.element[2].id, rectangle.indice_count);
  
  temp_text_print_line("Hello World!");
  temp_text_print_line("Is this thing working?");
  console_caret = console_start_position;
  return 1;
}
