
struct
CollidableRect
{
  v3 min, max;
};

bool32
collision_test(CollidableRect a, CollidableRect b)
{
  if (a.max.x < b.min.x || a.min.x > b.max.x) return 0;
  if (a.max.y < b.min.y || a.min.y > b.max.y) return 0;
  if (a.max.z < b.min.z || a.min.z > b.max.z) return 0;
  return 1;
}

v3
collision_screen_picking(m4* projection_matrix, m4* view_matrix,
			 v3* cursor_pos, float window_width, float window_height)
{
  float cursor_x_norm = ((2.0f * cursor_pos->x) / window_width) - 1.0f;
  float cursor_y_norm = 1.0f - ((2.0f * cursor_pos->y) / window_height);
  v4 ray_world, ray_eye;
  v4 homogeneous_clip_coord(cursor_x_norm, cursor_y_norm, -1.0f, 1.0f);
  
  ray_eye = homogeneous_clip_coord * math_invert(projection_matrix);
  ray_eye = v4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);
  ray_world = ray_eye * math_invert(view_matrix);
  
  v3 cursor_ray(ray_world.x, ray_world.y, ray_world.z);
  return math_normalize(cursor_ray);
}
