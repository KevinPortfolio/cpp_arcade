

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
