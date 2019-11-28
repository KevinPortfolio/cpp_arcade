
static RenderObject glyph_render_obj[95]{};

static v3 console_start_position;
static v3 console_caret;

void
temp_text_print_line(Font &font, char* text)
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

void
gpu_alloc_font(Font *font)
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
		       {0.0f, 0.0f, 0.0f, (float32)font->glyph_width[glyph_index],
			0.0f, 0.0f, 0.0f, (float32)font->glyph_height[glyph_index], 0.0f,
			(float32)font->glyph_width[glyph_index],
			(float32)font->glyph_height[glyph_index], 0.0f,};
    
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

    render_allocate_texture(&font->texture_id[glyph_index], font->glyph_data[glyph_index],
		   font->glyph_width[glyph_index], font->glyph_height[glyph_index], 4);
    
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

void
gpu_alloc_line(RenderObject *render_object, v3 point_a, v3 point_b)
{
  ObjectMesh line_mesh;
  line_mesh.vertice_arr_size = 6;
  line_mesh.color_arr_size = 6;
  
  line_mesh.vertice = new float32[line_mesh.vertice_arr_size] {
				   point_a.x, point_a.y, point_a.z, point_b.x, point_b.y, point_b.z };  
  line_mesh.color = new float32[line_mesh.color_arr_size]{ 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
  
  render_object->vertice_count = 2;
  render_object->element[0].id = render_alloc_and_fill_buffer(line_mesh.vertice,
			   line_mesh.vertice_arr_size * sizeof(float32), ARRAY_BUFFER);
  render_object->element[1].id = render_alloc_and_fill_buffer(line_mesh.color, 
                            line_mesh.color_arr_size * sizeof(float32), ARRAY_BUFFER);

  delete[] line_mesh.vertice;
  delete[] line_mesh.color;
  
  render_object->element_count = 2;
  render_object->element[0].count_per_subset = 3;
  render_object->element[0].bytes_per_subset = render_object->element[0].count_per_subset * sizeof(float32);
  render_object->element[0].data_type = RENDER_DATA_TYPE_FLOAT;
  render_object->element[1].count_per_subset = 3;
  render_object->element[1].bytes_per_subset = render_object->element[1].count_per_subset * sizeof(float32);
  render_object->element[1].data_type = RENDER_DATA_TYPE_FLOAT; 
  
  render_create_object(render_object);  
}


void
gpu_alloc_rectangle(RenderObject *render_object, float width, float height)
{
  ObjectMesh rectangle_mesh;  
  rectangle_mesh.vertice_arr_size = 12;
  rectangle_mesh.texture_coord_arr_size = 8;
  rectangle_mesh.indice_arr_size = 6;
  
  rectangle_mesh.texture_coord = new float32[rectangle_mesh.texture_coord_arr_size]
					    { 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };
  
  rectangle_mesh.indice = new uint32[rectangle_mesh.indice_arr_size] { 0, 1, 3, 3, 2, 0 };
  
  rectangle_mesh.vertice = new float32[rectangle_mesh.vertice_arr_size]
				      { 0.0f, 0.0f, 0.0f, width, 0.0f, 0.0f, 0.0f, height, 0.0f,
				       width, height, 0.0f };
    
  render_object->vertice_count = 4;
  render_object->indice_count = 6;
  render_object->element[0].id = render_alloc_and_fill_buffer(rectangle_mesh.vertice,
	       rectangle_mesh.vertice_arr_size * sizeof(float32), ARRAY_BUFFER);
    
  render_object->element[1].id = render_alloc_and_fill_buffer(rectangle_mesh.texture_coord,
	    rectangle_mesh.texture_coord_arr_size * sizeof(float32), ARRAY_BUFFER);
    
  render_object->element[2].id = render_alloc_and_fill_buffer(rectangle_mesh.indice,
	    rectangle_mesh.indice_arr_size * sizeof(uint32), ELEMENT_ARRAY_BUFFER);
    
  render_object->element_count = 2;
  render_object->element[0].count_per_subset = 3;
  render_object->element[0].bytes_per_subset = render_object->element[0].count_per_subset * sizeof(float32);
  render_object->element[0].data_type = RENDER_DATA_TYPE_FLOAT;
  
  render_object->element[1].count_per_subset = 2;
  render_object->element[1].bytes_per_subset = render_object->element[1].count_per_subset * sizeof(float32);
  render_object->element[1].data_type = RENDER_DATA_TYPE_FLOAT;
    
  render_object->element[2].count_per_subset = 3;
  render_object->element[2].bytes_per_subset = render_object->element[1].count_per_subset * sizeof(uint32);
  render_object->element[2].data_type = RENDER_DATA_TYPE_UNSIGNED_INT; 

  render_bind_buffer(render_object->element[2].id, ELEMENT_ARRAY_BUFFER);
  render_create_object(render_object);
  
  delete[] rectangle_mesh.vertice;
  delete[] rectangle_mesh.texture_coord;
  delete[] rectangle_mesh.indice;
}


void
draw_render_iteration(RenderIteration* render_iteration)  
{
  if (render_iteration->render_object)
  {
    m4 model_mat = math_identity_mat();
      
    for (uint32 index = 0; index < render_iteration->render_count; index++)
    {
      model_mat = math_translate(model_mat, render_iteration->position[index]);
      render_update_mat4x4(2, model_mat.arr);
      model_mat = math_identity_mat();

      if (render_iteration->render_object->indice_count)
      {
	render_draw(render_iteration->render_object->id, render_iteration->render_object->element[2].id,
		    render_iteration->render_object->indice_count);
      }
      else
      {
	render_draw(render_iteration->render_object->id, 0, render_iteration->render_object->vertice_count,
		    RENDER_MODE_LINES);
      }
      
    }
  }
}
