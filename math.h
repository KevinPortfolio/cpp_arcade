#define PI 3.141592653589793f

union v3
{
  struct
  {
    float32 x,y,z;
  };
  struct
  {
    float32 r,g,b;
  };
  float32 arr[3];

  v3() : x(0.0f), y(0.0f), z(0.0f){}
  v3(float X, float Y, float Z)
  {
    x = X;
    y = Y;
    z = Z;
  }

  v3& operator=(v3& vec)
  {
     x = vec.x; y = vec.y; z = vec.z;
     return *this;
  }
};

union v4
{
  struct
  {
    float32 x,y,z,w;
  };
  struct
  {
    float32 r,g,b,a;
  };
  float32 arr[4];

  v4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f){}
  v4(float X, float Y, float Z, float W)
  {
    x = X;
    y = Y;
    z = Z;
    w = W;
  }

  v4& operator=(v4& vec)
  {
    x = vec.x; y = vec.y; z = vec.z; w = vec.w;
    return *this;
  }
};

union m4
{
  struct
  {
    float a, b, c, d;
    float e, f, g, h;
    float i, j, k, l;
    float m, n, o, p;
  };
  float rc[4][4];
  float arr[16];
  
  m4()
  {
    for (int row = 0; row < 4; row++) {
      for (int col = 0; col < 4; col++) {
	rc[row][col] = 0.0f;
      }
    }
    rc[0][0] = 1.0f; rc[1][1] = 1.0f; rc[2][2] = 1.0f; rc[3][3] = 1.0f;
  }
  
  m4&
  operator=(const m4& b)
  {
     for (int row = 0; row < 4; row++)
     {
      for (int col = 0; col < 4; col++)
      {
       rc[row][col] = b.rc[row][col];
      }
     }
     return *this;
  }
};

inline v3
operator+(v3& a, v3& b)
{
  v3 result(a.x + b.x, a.y + b.y, a.z + b.z);
  return(result);
}

inline v3
operator-(v3& a, v3& b)
{
  v3 result(a.x - b.x, a.y - b.y, a.z - b.z);
  return(result);
}

inline v3
operator*(float a, v3 &b)
{
  v3 result(a * b.x, a * b.y, a * b.z);
  return(result);
}

inline v3
operator*(v3 &b, float a)
{
  return(a * b);
}

inline v3
operator*(v3 &a, v3 &b)
{
  v3 result(a.x * b.x, a.y * b.y, a.z * b.z);
  return(result);
}

inline v4
operator*(v4 &a, v4 &b)
{
  v4 result(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
  return(result);
}

inline float
math_abs_val(float a)
{
  if (a < 0.0f)
    return -a;
  else
    return a;
}

inline float
math_floor(float a)
{
  int result = (int)a;
  if (a < 0)
    result -= 1;
  return((float)result);
}

inline float
Math_Round(float a)
{
  return math_floor(a + 0.5f);
}

inline float
math_inner_product(v3& a, v3& b)
{
  return(a.x * b.x + a.y * b.y + a.z * b.z);
}

inline float
Math_DegToRad(float degrees)
{
  return degrees * 0.01745329251994329576923690768489f;
}

float
math_square_root(float a)
{
  float result = a * 0.5f; //TODO: Find a better initial guess.
  float half_value = result, precision = 0.0000001f;
  unsigned int i;
  
  if (a == 1.0f)
    return 1.0f;
  else if (a == 0.0f)
    return 0.0f;
  else if (a < 0.0f)
    return -1.0f; // Error
  
  for (i = 0; i < 100; i++)
  {
    result -= (result * 0.5f) - (half_value / result);
    if (math_abs_val(result) <= precision)
      break;
  }
  return(result);
}

v4
operator*(const m4& a, const v4& b)
{
	v4 result;
	int a_row, a_col;
	for (a_row = 0; a_row < 4; a_row++) { 
		for (a_col = 0; a_col < 4; a_col++) {
			result.arr[a_row] += a.rc[a_row][a_col] * b.arr[a_col];
		}
	}
	return(result);
}

v4
operator*(const v4& a, const m4& b)
{
  v4 result;
  int a_row, a_col;
  for (a_row = 0; a_row < 4; a_row++) {
    for (a_col = 0; a_col < 4; a_col++) {
      result.arr[a_row] += b.rc[a_row][a_col] * a.arr[a_col];
    }
  }
  return(result);
}


inline float
math_magnitude(v3 &a)
{
  float result = math_inner_product(a, a);
  result = math_square_root(result);
  return(result);
}

inline v3
math_normalize(v3 &a)
{
  v3 result;
  float magnitude = math_magnitude(a);
  
  if (magnitude != 0)
    result = a * (1.0f / math_magnitude(a));
  return(result);
}

v3
math_cross_product(v3 &a, v3 &b)
{
  v3 result;
  result.x = (a.y * b.z) - (a.z * b.y);
  result.y = (a.z * b.x) - (a.x * b.z);
  result.z = (a.x * b.y) - (a.y * b.x);
  return(result);
}

m4
math_identity_mat()
{
  m4 result;
  result.rc[0][0] = 1.0f;
  result.rc[1][1] = 1.0f;
  result.rc[2][2] = 1.0f;
  result.rc[3][3] = 1.0f;
  return(result);
}

int
math_factorial(int a)
{
  int result = a;
  for (int i = 1; i < a; i++)
    result *= (a - i);
  return(result);
}

float
math_power(float base, int exponent)
{
  float result = 1.0f;
  while (exponent)
  {    
    if (exponent & 1)
      result *= base;
    exponent >>= 1;
    base *= base;
  }
  return(result);
}

float
math_sine(float radians)
{
  float result;
  unsigned int i;
  bool sign_flip = false;
  while (radians < -PI)
    radians += 2.0f * PI;
  while (radians > PI)
    radians -= 2.0f * PI;
  result = radians;
  
  //TODO: Pre-compute the factorials on startup.
  for (i = 3; i < 11; i = i + 2)
  {
    if (sign_flip)
    {
      result += math_power(radians, i) / math_factorial(i);
      sign_flip = 0;
    }
    else
    {
      result -= math_power(radians, i) / math_factorial(i);
      sign_flip = 1;
    }
  }
  return(result);
}

float
math_cosine(float radians)
{
  float Result = 1;
  unsigned int i;
  bool FlipSign = false;
  while (radians < -PI)
    radians += 2.0f * PI;
  while (radians > PI)
    radians -= 2.0f * PI;
  
  //TODO: Pre-compute the factorials on startup.
  for (i = 2; i < 11; i = i + 2)
  {
    if (FlipSign)
    {
      Result += math_power(radians, i) / math_factorial(i);
      FlipSign = 0;
    }
    else
    {
      Result -= math_power(radians, i) / math_factorial(i);
      FlipSign = 1;
    }
  }
  return(Result);
}

inline float
math_tangent(float radians)
{
  return (math_sine(radians) / math_cosine(radians));
}

m4
math_translate(m4 &matrix, v3 &vector)
{
  m4 result = matrix;
  result.rc[3][0] += vector.arr[0];
  result.rc[3][1] += vector.arr[1];
  result.rc[3][2] += vector.arr[2];
  return(result);
}

m4
math_ortho_mat(float left, float right, float bottom, float top, float near, float far,
	       unsigned short reverse_z_axis)
{
  m4 mat;
  mat.rc[0][0] = 2.0f / (right- left);
  mat.rc[1][1] = 2.0f / (top - bottom);
  // NOTE: ((-ReverseZAxis * 2.0f) + 1.0f) is purely to change the direction of the Z-axis.
  mat.rc[2][2] = ((-reverse_z_axis * 2.0f) + 1.0f) * 2.0f / (far - near);
  mat.rc[3][0] = -(right+ left) / (right- left);
  mat.rc[3][1] = -(top + bottom) / (top - bottom);
  mat.rc[3][2] = -(far + near) / (far - near);
  return(mat);
}

m4
math_lookat_mat(v3 &pos_eye, v3 &pos_target, v3 &vec_up)
{
  m4 result_mat;
  v3 delta_look, z_axis, x_axis, y_axis, cross;
  
  delta_look = pos_target - pos_eye;
  z_axis = math_normalize(delta_look); // (0, 0, -1);
  cross = math_cross_product(z_axis, vec_up);
  x_axis = math_normalize(cross); // (1, 0, 0);
  y_axis = math_cross_product(x_axis, z_axis); // (0, 1, 0); 
  
  result_mat.rc[0][0] = x_axis.x;
  result_mat.rc[0][1] = y_axis.x;
  result_mat.rc[0][2] = -z_axis.x;
  result_mat.rc[1][0] = x_axis.y;
  result_mat.rc[1][1] = y_axis.y;
  result_mat.rc[1][2] = -z_axis.y;
  result_mat.rc[2][0] = x_axis.z;
  result_mat.rc[2][1] = y_axis.z;
  result_mat.rc[2][2] = -z_axis.z;
  result_mat.rc[3][0] = -math_inner_product(x_axis, pos_eye);
  result_mat.rc[3][1] = -math_inner_product(y_axis, pos_eye);
  result_mat.rc[3][2] = math_inner_product(z_axis, pos_eye);
  result_mat.rc[3][3] = 1.0f;
  return(result_mat);
}

m4
math_perspective_mat(float field_of_view, float aspect_ratio, float plane_near, float plane_far)
{
  m4 result;
  float half_val = (float)math_tangent(field_of_view * 0.5f);
  result.rc[0][0] = 1.0f / (aspect_ratio * half_val);
  result.rc[0][1] = 0;
  result.rc[0][2] = 0;
  result.rc[0][3] = 0;
  
  result.rc[1][0] = 0;
  result.rc[1][1] = 1.0f / half_val;
  result.rc[1][2] = 0;
  result.rc[1][3] = 0;
  
  result.rc[2][0] = 0;
  result.rc[2][1] = 0;
  result.rc[2][2] = -(plane_far + plane_near) / (plane_far - plane_near);
  result.rc[2][3] = -1.0f;
  
  result.rc[3][0] = 0;
  result.rc[3][1] = 0;
  result.rc[3][2] = -(2.0f * plane_far * plane_near) / (plane_far - plane_near);
  result.rc[3][3] = 0;
  return(result);
}

m4
math_invert(m4 *mat)
{
  m4 inverse_mat, result;
  float det;
  int i;
  
  inverse_mat.arr[0] = mat->arr[5] * mat->arr[10] * mat->arr[15] -
    mat->arr[5] * mat->arr[11] * mat->arr[14] -
    mat->arr[9] * mat->arr[6] * mat->arr[15] +
    mat->arr[9] * mat->arr[7] * mat->arr[14] +
    mat->arr[13] * mat->arr[6] * mat->arr[11] -
    mat->arr[13] * mat->arr[7] * mat->arr[10];
  
  inverse_mat.arr[4] = -mat->arr[4] * mat->arr[10] * mat->arr[15] +
    mat->arr[4] * mat->arr[11] * mat->arr[14] +
    mat->arr[8] * mat->arr[6] * mat->arr[15] -
    mat->arr[8] * mat->arr[7] * mat->arr[14] -
    mat->arr[12] * mat->arr[6] * mat->arr[11] +
    mat->arr[12] * mat->arr[7] * mat->arr[10];
  
  inverse_mat.arr[8] = mat->arr[4] * mat->arr[9] * mat->arr[15] -
    mat->arr[4] * mat->arr[11] * mat->arr[13] -
    mat->arr[8] * mat->arr[5] * mat->arr[15] +
    mat->arr[8] * mat->arr[7] * mat->arr[13] +
    mat->arr[12] * mat->arr[5] * mat->arr[11] -
    mat->arr[12] * mat->arr[7] * mat->arr[9];
  
  inverse_mat.arr[12] = -mat->arr[4] * mat->arr[9] * mat->arr[14] +
    mat->arr[4] * mat->arr[10] * mat->arr[13] +
    mat->arr[8] * mat->arr[5] * mat->arr[14] -
    mat->arr[8] * mat->arr[6] * mat->arr[13] -
    mat->arr[12] * mat->arr[5] * mat->arr[10] +
    mat->arr[12] * mat->arr[6] * mat->arr[9];
  
  inverse_mat.arr[1] = -mat->arr[1] * mat->arr[10] * mat->arr[15] +
    mat->arr[1] * mat->arr[11] * mat->arr[14] +
    mat->arr[9] * mat->arr[2] * mat->arr[15] -
    mat->arr[9] * mat->arr[3] * mat->arr[14] -
    mat->arr[13] * mat->arr[2] * mat->arr[11] +
    mat->arr[13] * mat->arr[3] * mat->arr[10];
  
  inverse_mat.arr[5] = mat->arr[0] * mat->arr[10] * mat->arr[15] -
    mat->arr[0] * mat->arr[11] * mat->arr[14] -
    mat->arr[8] * mat->arr[2] * mat->arr[15] +
    mat->arr[8] * mat->arr[3] * mat->arr[14] +
    mat->arr[12] * mat->arr[2] * mat->arr[11] -
    mat->arr[12] * mat->arr[3] * mat->arr[10];
  
  inverse_mat.arr[9] = -mat->arr[0] * mat->arr[9] * mat->arr[15] +
    mat->arr[0] * mat->arr[11] * mat->arr[13] +
    mat->arr[8] * mat->arr[1] * mat->arr[15] -
    mat->arr[8] * mat->arr[3] * mat->arr[13] -
    mat->arr[12] * mat->arr[1] * mat->arr[11] +
    mat->arr[12] * mat->arr[3] * mat->arr[9];
  
  inverse_mat.arr[13] = mat->arr[0] * mat->arr[9] * mat->arr[14] -
    mat->arr[0] * mat->arr[10] * mat->arr[13] -
    mat->arr[8] * mat->arr[1] * mat->arr[14] +
    mat->arr[8] * mat->arr[2] * mat->arr[13] +
    mat->arr[12] * mat->arr[1] * mat->arr[10] -
    mat->arr[12] * mat->arr[2] * mat->arr[9];
  
  inverse_mat.arr[2] = mat->arr[1] * mat->arr[6] * mat->arr[15] -
    mat->arr[1] * mat->arr[7] * mat->arr[14] -
    mat->arr[5] * mat->arr[2] * mat->arr[15] +
    mat->arr[5] * mat->arr[3] * mat->arr[14] +
    mat->arr[13] * mat->arr[2] * mat->arr[7] -
    mat->arr[13] * mat->arr[3] * mat->arr[6];
  
  inverse_mat.arr[6] = -mat->arr[0] * mat->arr[6] * mat->arr[15] +
    mat->arr[0] * mat->arr[7] * mat->arr[14] +
    mat->arr[4] * mat->arr[2] * mat->arr[15] -
    mat->arr[4] * mat->arr[3] * mat->arr[14] -
    mat->arr[12] * mat->arr[2] * mat->arr[7] +
    mat->arr[12] * mat->arr[3] * mat->arr[6];
  
  inverse_mat.arr[10] = mat->arr[0] * mat->arr[5] * mat->arr[15] -
    mat->arr[0] * mat->arr[7] * mat->arr[13] -
    mat->arr[4] * mat->arr[1] * mat->arr[15] +
    mat->arr[4] * mat->arr[3] * mat->arr[13] +
    mat->arr[12] * mat->arr[1] * mat->arr[7] -
    mat->arr[12] * mat->arr[3] * mat->arr[5];
  
  inverse_mat.arr[14] = -mat->arr[0] * mat->arr[5] * mat->arr[14] +
    mat->arr[0] * mat->arr[6] * mat->arr[13] +
    mat->arr[4] * mat->arr[1] * mat->arr[14] -
    mat->arr[4] * mat->arr[2] * mat->arr[13] -
    mat->arr[12] * mat->arr[1] * mat->arr[6] +
    mat->arr[12] * mat->arr[2] * mat->arr[5];
  
  inverse_mat.arr[3] = -mat->arr[1] * mat->arr[6] * mat->arr[11] +
    mat->arr[1] * mat->arr[7] * mat->arr[10] +
    mat->arr[5] * mat->arr[2] * mat->arr[11] -
    mat->arr[5] * mat->arr[3] * mat->arr[10] -
    mat->arr[9] * mat->arr[2] * mat->arr[7] +
    mat->arr[9] * mat->arr[3] * mat->arr[6];
  
  inverse_mat.arr[7] = mat->arr[0] * mat->arr[6] * mat->arr[11] -
    mat->arr[0] * mat->arr[7] * mat->arr[10] -
    mat->arr[4] * mat->arr[2] * mat->arr[11] +
    mat->arr[4] * mat->arr[3] * mat->arr[10] +
    mat->arr[8] * mat->arr[2] * mat->arr[7] -
    mat->arr[8] * mat->arr[3] * mat->arr[6];
  
  inverse_mat.arr[11] = -mat->arr[0] * mat->arr[5] * mat->arr[11] +
    mat->arr[0] * mat->arr[7] * mat->arr[9] +
    mat->arr[4] * mat->arr[1] * mat->arr[11] -
    mat->arr[4] * mat->arr[3] * mat->arr[9] -
    mat->arr[8] * mat->arr[1] * mat->arr[7] +
    mat->arr[8] * mat->arr[3] * mat->arr[5];
  
  inverse_mat.arr[15] = mat->arr[0] * mat->arr[5] * mat->arr[10] -
    mat->arr[0] * mat->arr[6] * mat->arr[9] -
    mat->arr[4] * mat->arr[1] * mat->arr[10] +
    mat->arr[4] * mat->arr[2] * mat->arr[9] +
    mat->arr[8] * mat->arr[1] * mat->arr[6] -
    mat->arr[8] * mat->arr[2] * mat->arr[5];
  
  det = mat->arr[0] * inverse_mat.arr[0] + mat->arr[1] * inverse_mat.arr[4] +
    mat->arr[2] * inverse_mat.arr[8] + mat->arr[3] * inverse_mat.arr[12];
  if (det == 0)
    return result;
  det = 1.0f / det;
  for (i = 0; i < 16; i++)
    result.arr[i] = inverse_mat.arr[i] * det;
  return result;
}
