#include <stdlib.h> // TODO: Make custom random number generator.

struct
BlockGroup
{
  v3 position;
  uint8 type;
  uint8 rotation;
};

static RenderObject game_block;
static BlockGroup block_instance[100]{};
static uint32 block_instance_count;
static uint32 image_id[7];

void
load_block_fall(GameState* game_state)
{
  float block_height = 24.0f;
  
  gpu_alloc_rectangle(&game_block, block_height, block_height);

  block_instance_count = 1;
  block_instance[block_instance_count - 1].position =
    v3(400.0f, game_state->window_height - block_height, 0.0f);
  block_instance[block_instance_count - 1].type = 0;
  block_instance[block_instance_count - 1].rotation = rand() % 4;

  game_state->module_id = 3; // NOTE: Do not delete this yet.


  byte *image_data;
  int image_width = 0, image_height = 0, image_bytes_per_pixel = 0;
  char *image_path[7] = {"img/blue_block.png", "img/green_block.png", "img/orange_block.png",
			 "img/purple_block.png", "img/red_block.png", "img/teal_block.png",
			 "img/yellow_block.png"};
  
  for (uint32 index = 0; index < 7; index++)
  {
    image_data = stbi_load(image_path[index], &image_width, &image_height, &image_bytes_per_pixel, 0);
    render_allocate_texture(&image_id[index], image_data, image_width, image_height,
			    image_bytes_per_pixel);
    delete[] image_data;
    image_data = 0;
  }
			
}

void // NOTE: Temporary inefficient solution.
draw_block_group(BlockGroup object, float block_height)
{
  m4 identity_mat = math_identity_mat();
  m4 model_mat;
  v3 position[4] = { object.position, object.position, object.position, object.position};
    
  switch (object.type)
  {
  case 0:
    {
      if ((object.rotation == 1) || (object.rotation == 3))
      {
	position[1].y -= block_height;
	position[2].y = position[1].y - block_height;
	position[3].y = position[2].y - block_height;
      }
      else
      {
	position[1].x += block_height;
	position[2].x = position[1].x + block_height;
	position[3].x = position[2].x + block_height;
      }
            
    } break;
  case 1:
    {
      position[1].x += block_height;
      position[2].x += block_height;
      position[2].y -= block_height;
      position[3].y -= block_height;

    } break;
    case 2:
    {
      if (object.rotation == 0)
      {
	position[1].x -= block_height;
	position[2].x += block_height;
	position[3].y -= block_height;
      }
      else if (object.rotation == 1)
      {
	position[0].x += block_height;
	position[1].y -= block_height;
	position[2].y -= block_height;
	position[2].x += block_height;
	position[3].x += block_height;
	position[3].y = position[1].y - block_height;
      }
      else if (object.rotation == 2)
      {
	position[0].x += block_height;
	position[1].y -= block_height;
	position[2].x += block_height;
	position[2].y -= block_height;
	position[3].y -= block_height;
	position[3].x = position[2].x + block_height;
      }
      else if (object.rotation == 3)
      {
	position[1].y -= block_height;
	position[2].y -= block_height;
	position[2].x += block_height;
	position[3].y = position[1].y - block_height;
      }
	    
    } break;
  case 3:
    {
      if (object.rotation == 0)
      {
	position[1].y -= block_height;
	position[2].x += block_height;
	position[3].x = position[2].x + block_height;
      }
      else if (object.rotation == 1)
      {
	position[1].x += block_height;
	position[2].x += block_height;
	position[2].y -= block_height;
	position[3].x += block_height;
	position[3].y = position[2].y - block_height;
      }
      else if (object.rotation == 2)
      {
	position[0].y -= block_height;
	position[1].x += block_height;
	position[1].y -= block_height;
	position[2].y -= block_height;
	position[2].x = position[1].x + block_height;
	position[3].x = position[1].x + block_height;
      }
      else if (object.rotation == 3)
      {
	position[1].y -= block_height;
	position[2].y = position[1].y - block_height;
	position[3].x += block_height;
	position[3].y = position[1].y - block_height;
      }
           
    } break;
  case 4:
    {
      if (object.rotation == 0)
      {
	position[1].x += block_height;
	position[2].x = position[1].x + block_height;
	position[3].x = position[1].x + block_height;
	position[3].y -= block_height;
      }
      else if (object.rotation == 1)
      {
	position[0].x += block_height;
	position[1].x += block_height;
	position[1].y -= block_height;
	position[2].x += block_height;
	position[2].y = position[1].y - block_height;
	position[3].y = position[1].y - block_height;
      }
      else if (object.rotation == 2)
      {
	position[1].y -= block_height;
	position[2].x += block_height;
	position[2].y -= block_height;
	position[3].x = position[2].x + block_height;
	position[3].y -= block_height;
      }
      else if (object.rotation == 3)
      {
	position[1].x += block_height;
	position[2].y -= block_height;
	position[3].y = position[2].y - block_height;
      }
    
    } break;
  case 5:
    {
      if ((object.rotation == 1) || (object.rotation == 3))
      {
	position[0].x += block_height;
	position[1].y -= block_height;
	position[1].x += block_height;
	position[2].y -= block_height;
	position[3].y = position[1].y - block_height;
      }
      else
      {
	position[1].x += block_height;
	position[2].x += block_height;
	position[2].y -= block_height;
	position[3].x = position[1].x + block_height;
	position[3].y -= block_height;
      }

    } break;
  case 6:
    {
      if ((object.rotation == 1) || (object.rotation == 3))
      {
	position[1].y -= block_height;
	position[2].y -= block_height;
	position[2].x += block_height;
	position[3].y = position[1].y - block_height;
	position[3].x += block_height;
      }
      else
      {
	position[0].y -= block_height;
	position[1].x += block_height;
	position[1].y -= block_height;
	position[2].x += block_height;
	position[3].x = position[1].x + block_height;
      }
      
    } break;
  default:
    {} break;
  }

  for (int index = 0; index < 4; index++)
  {
    model_mat = math_translate(identity_mat, position[index]);
    render_update_mat4x4(2, model_mat.arr);
    render_draw(game_block.id, game_block.element[2].id, game_block.indice_count);
  }
}

static bool previous = 0;
static bool prev_a = 0;
static bool prev_d = 0;

void
block_fall_loop(GameState* game_state)
{
  float block_height = 24.0f;
  uint32 current_block = block_instance_count - 1;
  
  if (game_state->keyboard['a'] && (prev_a == 0))
  {
    block_instance[current_block].position.x -= block_height;
    prev_a = 1;
  }
  else if (!game_state->keyboard['a'])
    prev_a = 0;

  if (game_state->keyboard['d'] && (prev_d == 0))
  {
    block_instance[current_block].position.x += block_height;
    prev_d = 1;
  }
  else if (!game_state->keyboard['d'])
    prev_d = 0;
  
  if (game_state->keyboard[' '] && (previous == 0))
  {
    block_instance[current_block].rotation++;
    previous = 1;
  }
  else if (!game_state->keyboard[' '])
    previous = 0;

  if (block_instance[current_block].rotation >= 4)
    block_instance[current_block].rotation = 0;
  
  render_use_shader(game_state->shader_id);
  render_update_mat4x4(3, game_state->camera->view_mat.arr);
  render_update_mat4x4(4, game_state->camera->projection_mat.arr);
  render_update_int(5, 0);

  for (uint32 index = 0; index < block_instance_count; index++)
  {
    render_bind_texture(image_id[block_instance[index].type]);    
    draw_block_group(block_instance[index], block_height);
  }
  
  render_bind_texture(0);
  
  if (block_instance[current_block].position.y >
      (0.0f + (block_height * 4)))
  {
    block_instance[current_block].position.y -= block_height * 0.005f;
  }
  else
  {
    if (block_instance_count <= 100)
    {
      static uint8 type = 0;
      float x = 400.0f + (rand() % (uint32)((600 - (block_height * 3)) / block_height)) * block_height;
      block_instance[block_instance_count].position =
	v3(x, game_state->window_height - block_height, 0.0f);
      block_instance[block_instance_count].type = rand() % 7;

      block_instance[block_instance_count].rotation = rand() % 4;
      
      if (block_instance_count <= 100)
	block_instance_count++;
    }
  }
  
}
