#if !defined(OPENGL_H)
#define OPENGL_H

#define GL_NO_ERROR                       0
#define GL_INVALID_ENUM                   0x0500
#define GL_INVALID_VALUE                  0x0501
#define GL_INVALID_OPERATION              0x0502
#define GL_STACK_OVERFLOW                 0x0503
#define GL_STACK_UNDERFLOW                0x0504
#define GL_OUT_OF_MEMORY                  0x0505

#define GL_COMPILE_STATUS 0x8B81
#define GL_ATTACHED_SHADERS 0x8B85
#define GL_LINK_STATUS 0x8B82

#define GL_ARRAY_BUFFER 0x8892

#define GL_STATIC_DRAW 0x88E4
  

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;

typedef GLuint __stdcall gl_create_shader(GLenum shaderType);
typedef void __stdcall gl_shader_source(GLuint shader, GLsizei count, const char** string, const GLint* length);
typedef void __stdcall gl_compile_shader(GLuint shader);
typedef void __stdcall gl_delete_shader(GLuint shader);
typedef GLuint __stdcall gl_create_program(void);
typedef void __stdcall gl_attach_shader(GLuint program, GLuint shader);
typedef void __stdcall gl_link_program(GLuint program);
typedef void __stdcall gl_detach_shader(GLuint program, GLuint shader);
typedef void __stdcall gl_get_shader_iv(GLuint shader, GLenum pname, GLint* params);
typedef void __stdcall gl_get_program_iv(GLuint program, GLenum pname, GLint* params);
typedef void __stdcall gl_get_shader_info_log(GLuint shader, GLsizei maxLength, GLsizei* length, char* infoLog);
typedef void __stdcall gl_get_program_info_log(GLuint program, GLsizei maxLength, GLsizei* length, char* infoLog);
typedef void __stdcall gl_use_program(GLuint program);
typedef void __stdcall gl_delete_program(GLuint program);

typedef void __stdcall gl_gen_buffers(GLsizei n, GLuint* buffers);
typedef void __stdcall gl_bind_buffer(GLenum target, GLuint buffer);
typedef void __stdcall gl_buffer_data(GLenum target, ptrdiff_t size, const GLvoid* data, GLenum usage);

typedef void __stdcall gl_gen_vertex_arrays(GLsizei n, GLuint* arrays);
typedef void __stdcall gl_bind_vertex_array(GLuint arr);
typedef void __stdcall gl_delete_vertex_arrays(GLsizei n, const GLuint* arrays);
typedef void __stdcall gl_vertex_attrib_pointer(GLuint index, GLint size, GLenum type,
						GLboolean normalized, GLsizei stride, const GLvoid* pointer);
typedef void __stdcall gl_enable_vertex_attrib_array(GLuint index);

static gl_create_shader* glCreateShader;
static gl_shader_source* glShaderSource;
static gl_compile_shader* glCompileShader;
static gl_delete_shader* glDeleteShader;
static gl_create_program* glCreateProgram;
static gl_attach_shader* glAttachShader;
static gl_link_program* glLinkProgram;
static gl_detach_shader* glDetachShader;
static gl_get_shader_info_log* glGetShaderInfoLog;
static gl_get_program_info_log* glGetProgramInfoLog;
static gl_get_shader_iv* glGetShaderiv;
static gl_get_program_iv* glGetProgramiv;
static gl_use_program* glUseProgram;
static gl_delete_program* glDeleteProgram;

static gl_gen_buffers* glGenBuffers;
static gl_bind_buffer* glBindBuffer;
static gl_buffer_data* glBufferData;

static gl_enable_vertex_attrib_array* glEnableVertexAttribArray;
static gl_vertex_attrib_pointer* glVertexAttribPointer;
static gl_gen_vertex_arrays* glGenVertexArrays;
static gl_bind_vertex_array* glBindVertexArray;
static gl_delete_vertex_arrays* glDeleteVertexArrays;

void
opengl_load_functions()
{
  // OpenGL 2
  glCreateShader = (gl_create_shader*)wglGetProcAddress("glCreateShader");
  glShaderSource = (gl_shader_source*)wglGetProcAddress("glShaderSource");
  glCompileShader = (gl_compile_shader*)wglGetProcAddress("glCompileShader");
  glDeleteShader = (gl_delete_shader*)wglGetProcAddress("glDeleteShader");
  glCreateProgram = (gl_create_program*)wglGetProcAddress("glCreateProgram");
  glAttachShader = (gl_attach_shader*)wglGetProcAddress("glAttachShader");
  glLinkProgram = (gl_link_program*)wglGetProcAddress("glLinkProgram");
  glDetachShader = (gl_detach_shader*)wglGetProcAddress("glDetachShader");
  glGetShaderInfoLog = (gl_get_shader_info_log*)wglGetProcAddress("glGetShaderInfoLog");
  glGetProgramInfoLog = (gl_get_program_info_log*)wglGetProcAddress("glGetProgramInfoLog");
  glGetShaderiv = (gl_get_shader_iv*)wglGetProcAddress("glGetShaderiv");
  glGetProgramiv = (gl_get_program_iv*)wglGetProcAddress("glGetProgramiv");
  glUseProgram = (gl_use_program*)wglGetProcAddress("glUseProgram");
  glDeleteProgram = (gl_delete_program*)wglGetProcAddress("glDeleteProgram");
  
  glGenBuffers = (gl_gen_buffers*)wglGetProcAddress("glGenBuffers");
  glBindBuffer = (gl_bind_buffer*)wglGetProcAddress("glBindBuffer");
  glBufferData = (gl_buffer_data*)wglGetProcAddress("glBufferData");

  glVertexAttribPointer = (gl_vertex_attrib_pointer*)wglGetProcAddress("glVertexAttribPointer");
  glEnableVertexAttribArray = (gl_enable_vertex_attrib_array*)wglGetProcAddress("glEnableVertexAttribArray");

  // OpenGL 3
  glGenVertexArrays = (gl_gen_vertex_arrays*)wglGetProcAddress("glGenVertexArrays");
  glBindVertexArray = (gl_bind_vertex_array*)wglGetProcAddress("glBindVertexArray");
  glDeleteVertexArrays = (gl_delete_vertex_arrays*)wglGetProcAddress("glDeleteVertexArrays");
}

#endif