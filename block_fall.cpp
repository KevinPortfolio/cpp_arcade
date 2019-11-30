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

void
load_block_fall(GameState* game_state)
{
  float block_height = 24.0f;
  
  gpu_alloc_rectangle(&game_block, block_height, block_height);

  block_instance_count = 1;
  block_instance[block_instance_count - 1].position =
    v3(200.0f, game_state->window_height - block_height, 0.0f);
  block_instance[block_instance_count - 1].type = 0;
  block_instance[block_instance_count - 1].rotation = rand() % 4;

  game_state->module_id = 3; // NOTE: Do not delete this yet.
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

void
block_fall_loop(GameState* game_state)
{
  float block_height = 24.0f;
  
  render_use_shader(game_state->shader_id);
  render_update_mat4x4(3, game_state->camera->view_mat.arr);
  render_update_mat4x4(4, game_state->camera->projection_mat.arr);
  render_update_int(5, 0);

  render_bind_texture(game_state->texture_id);

  for (uint32 index = 0; index < block_instance_count; index++)
    draw_block_group(block_instance[index], block_height);
  
  render_bind_texture(0);
  
  if (block_instance[block_instance_count - 1].position.y >
      (0.0f + (block_height * 4)))
  {
    block_instance[block_instance_count - 1].position.y -= block_height * 0.01f;
  }
  else
  {
    if (block_instance_count <= 100)
    {
      static uint8 type = 0;
      float x = 200.0f + (rand() % (uint32)((1000 - (block_height * 3)) / block_height)) * block_height;
      block_instance[block_instance_count].position =
	v3(x, game_state->window_height - block_height, 0.0f);
      block_instance[block_instance_count].type = rand() % 7;

      block_instance[block_instance_count].rotation = rand() % 4;
      
      if (block_instance_count <= 100)
	block_instance_count++;
    }
  }
  
}
