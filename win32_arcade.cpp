typedef unsigned char byte;

typedef char int8;
typedef short int16;
typedef int int32;
typedef long long int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef float float32;
typedef double float64;

typedef int bool32;

#include "math.h"
#include "render.h"
#include "utility.h"
#include "arcade.h"
#include "utility.cpp"
File
platform_read_file(char* file_path);

#include "arcade.cpp"
#include <Windows.h>
#include "opengl_arcade.cpp"

// Accepted values for attribute names for the OpenGL Context(WGL)
#define WGL_CONTEXT_MAJOR_VERSION_ARB		     0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB		     0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB		     0x2093	
#define WGL_CONTEXT_FLAGS_ARB			     0x2094	
#define WGL_CONTEXT_PROFILE_MASK_ARB		     0x9126
#define WGL_CONTEXT_DEBUG_BIT_ARB		     0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB	     0x0002	
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB	     0X00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB    0X00000002

typedef HGLRC __stdcall wgl_create_context_attribs_arb(HDC hDC, HGLRC hShareContext,
						       const int* attribList);

File
platform_read_file(char* file_path)
{
  File result = {};
  DWORD bytes_read = 0;
  bool32 error;  
  HANDLE img_file = CreateFileA(file_path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING,
			 FILE_ATTRIBUTE_NORMAL, 0);
  
  if (img_file == INVALID_HANDLE_VALUE)
  {
    DWORD error_code = GetLastError(); // TODO: Resolve this error code cleanly
    return result;
  }
  
  result.byte_size = GetFileSize(img_file, 0);
  // NOTE: Add 1 for the NULL termination or overflow risk.
  result.data = new byte[result.byte_size + 1]{}; 
  error = ReadFile(img_file, (LPVOID)result.data, result.byte_size, &bytes_read, 0);
  if (bytes_read < result.byte_size)
  {
    // TODO: Only partial read of file completed.
  }
  if (error == 0)
  {
    // TODO: Check for error or asynchronous completion.
  }
  CloseHandle(img_file);
  return result;
}

char // TODO: Add UNICODE support
platform_create_font(const char* file_name, const char* font_name, int font_height, int font_weight,
		     int* return_height, long width_buf[256], long height_buf[256], unsigned char* data_buf[256])
{
  
  BYTE *bitmap_data = 0;
  SIZE font_size; 
  UINT32 *bmp_ptr, *glyph_buf_ptr, *bmp_row, pixel, pitch;
  INT32 bmp_width, bmp_height;
  UINT8 *glyph_buf_row, alpha;

  BITMAPINFO bitmap_info = {};
  bitmap_info.bmiHeader.biSize = sizeof(bitmap_info.bmiHeader);
  bitmap_info.bmiHeader.biWidth = 1024;
  bitmap_info.bmiHeader.biHeight = 1024;
  bitmap_info.bmiHeader.biPlanes = 1;
  bitmap_info.bmiHeader.biBitCount = 32;
  bitmap_info.bmiHeader.biCompression = BI_RGB;

  HDC device_context = CreateCompatibleDC(GetDC(0)); //TODO: Release this DC later
  
  if (device_context)
  {
    SetBkColor(device_context, RGB(0, 0, 0)); // NOTE: Set the background brush to black (default is white).
    
    // NOTE: Returns bottom up space. ptr at top
    HBITMAP font_bmp = CreateDIBSection(device_context, &bitmap_info, DIB_RGB_COLORS, (void**)& bitmap_data, 0, 0);
    // NOTE: Need to release bitmap

    if (!font_bmp)
      return -1;

    SelectObject(device_context, font_bmp);
    AddFontResourceExA(file_name, FR_PRIVATE, 0);
    
    HFONT font = CreateFontA(font_height, 0, 0, 0, font_weight, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		       CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, font_name);
    SelectObject(device_context, font);
    
    *return_height = font_height;
    
    TEXTMETRIC font_metrics;
    if (!GetTextMetrics(device_context, &font_metrics))
      OutputDebugStringA("Failed to get TextMetrics");
    
    for (char glyph= 32; glyph < 127; glyph++)
    {
      bmp_width = 1024;
      bmp_height = 1024;
      
      if (!GetTextExtentPoint32A(device_context, &glyph, 1, &font_size))
	OutputDebugStringA("ERROR: GetTextExtentPoint32W() Failed in platform_create_font()\n");
      width_buf[glyph] = font_size.cx;
      height_buf[glyph] = font_size.cy;
      
      if (SetTextColor(device_context, RGB(255, 255, 255)) == CLR_INVALID)
	OutputDebugStringA("ERROR: SetTextColor() Failed in platform_create_font()\n");
      if (!TextOutA(device_context, 0, 0, &glyph, 1))
	OutputDebugStringA("ERROR: TextOutW() Failed in platform_create_font()\n");
      
      data_buf[glyph] = new UCHAR[(INT64)font_size.cx * font_size.cy * 4]{};
      //NOTE: 4 because RGBA
      
      pitch = font_size.cx * 4;
      glyph_buf_row = data_buf[glyph] + (((UINT64)font_size.cy - 1) * pitch);
    
      bmp_row = (UINT32*)bitmap_data + (((UINT64)bmp_height - 1) * bmp_width);
      // NOTE: Initialize and move ptr to 
      
      for (INT32 y = 0; y < font_size.cy; y++)
      {
	bmp_ptr = (UINT32*)bmp_row;
	glyph_buf_ptr = (UINT32*)glyph_buf_row;
	for (INT32 x = 0; x < font_size.cx; x++)
	{
	  pixel = *bmp_ptr;
	  alpha = (UINT8)(*bmp_ptr & 0xFF);
	  *glyph_buf_ptr++ = ((alpha << 24) | (alpha << 16) | (alpha << 8) | (alpha << 0));
	  bmp_ptr++;
	}
	glyph_buf_row -= pitch;
	bmp_row -= bmp_width;
      }
    }
    
    if (font_bmp)
      DeleteObject(font_bmp);
    
    //    ReleaseDC(0, device_context);
    return 1;
  }
  return -1;
}

void
win32_opengl_init(HDC device_context)
{
  HGLRC opengl_context;
  PIXELFORMATDESCRIPTOR pixel_format_desc = {}, pixel_format_ideal_desc = {};
  pixel_format_ideal_desc.nSize = sizeof(pixel_format_ideal_desc);
  pixel_format_ideal_desc.nVersion = 1;
  pixel_format_ideal_desc.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
  pixel_format_ideal_desc.iPixelType = PFD_TYPE_RGBA;
  pixel_format_ideal_desc.cColorBits = 32;
  pixel_format_ideal_desc.cAlphaBits = 8;
  pixel_format_ideal_desc.cDepthBits = 16;
  pixel_format_ideal_desc.iLayerType = PFD_MAIN_PLANE;

// TODO: Use GetLastError() for more error information.
  int pixel_format_index = ChoosePixelFormat(device_context, &pixel_format_ideal_desc);
  if (pixel_format_index == 0)
    OutputDebugStringA("Obtaining a Pixel Format Index Failed!");

  if (!DescribePixelFormat(device_context, pixel_format_index,
			   sizeof(pixel_format_desc), &pixel_format_desc))
    OutputDebugStringA("Obtaining Description of a Pixel Format Failed!");

  if (!SetPixelFormat(device_context, pixel_format_index, &pixel_format_desc))
    OutputDebugStringA("Setting Pixel Format Failed!");

  opengl_context = wglCreateContext(device_context);
  if (opengl_context == 0)
    OutputDebugStringA("Obtaining OpenGL Render Context Failed!");

  if (!wglMakeCurrent(device_context, opengl_context))
    OutputDebugStringA("Failed to set the OpenGl Render Context to the Device Context");

  wgl_create_context_attribs_arb * wglCreateContextAttribsARB =
    (wgl_create_context_attribs_arb*)wglGetProcAddress("wglCreateContextAttribsARB");

  if (!wglCreateContextAttribsARB)
    OutputDebugStringA("Failed to obtain the OpenGL extension function.");

  int opengl_desc[] =
    {
		       WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		       WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		       WGL_CONTEXT_FLAGS_ARB,
		       WGL_CONTEXT_DEBUG_BIT_ARB,
		       WGL_CONTEXT_PROFILE_MASK_ARB,
		       WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
		       0
    };

  HGLRC opengl_modern_context = 0;
  if (wglCreateContextAttribsARB)
    opengl_modern_context =
      (HGLRC)(wglCreateContextAttribsARB(device_context, 0, opengl_desc));

  if (!opengl_modern_context) 
    OutputDebugStringA("Failed to obtain an OpenGL 3.2 or later context.");

  if (!wglMakeCurrent(device_context, opengl_modern_context))
    OutputDebugStringA("Failed to set the OpenGL context as the drawing surface.");

  wglDeleteContext(opengl_context);
  opengl_context = opengl_modern_context;
}

LRESULT CALLBACK
win32_msg_callback(HWND window_handle, UINT msg, WPARAM w_param, LPARAM l_param)
{
	LRESULT result = 0;

	switch (msg)
	{
	case WM_CREATE:
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		//Platform_ResizeWindow(RECTANGLE* NewWindowRect, int StartX, int StartY,
		//	0);
		break;
	case WM_KEYDOWN:
		if (w_param == VK_ESCAPE)
			PostQuitMessage(0);
		break;
	case WM_SIZE: 
		break;
	default:
		return DefWindowProc(window_handle, msg, w_param, l_param);
	}

	return result;
}

int WINAPI
WinMain(_In_ HINSTANCE dll_name, _In_opt_ HINSTANCE unused, _In_ LPSTR cmd_line_str,
	_In_ int display_flags)
{
	GameState game_state;
	game_state.window_width = 1700;
	game_state.window_height = 1000;

	WNDCLASSEXA win_class_info = {};
	win_class_info.cbSize = sizeof(WNDCLASSEX);
	win_class_info.lpszMenuName = 0;
	win_class_info.lpszClassName = "ARCADE";
	win_class_info.style = CS_HREDRAW | CS_VREDRAW; 
	win_class_info.lpfnWndProc = win32_msg_callback;
	win_class_info.cbClsExtra = 0;
	win_class_info.cbWndExtra = 0;
	win_class_info.hInstance = dll_name;
	win_class_info.hIcon = LoadIcon(0, IDI_APPLICATION);
	win_class_info.hCursor = LoadCursorA(0, IDC_ARROW);
	win_class_info.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	win_class_info.hIconSm = LoadIcon(0, IDI_APPLICATION);

	if (!RegisterClassExA(&win_class_info))
		OutputDebugStringA("Window Registration Failed!");

        RECT window_rect = { 0, 0, game_state.window_width, game_state.window_height };
	AdjustWindowRectEx(&window_rect, WS_OVERLAPPEDWINDOW, false, WS_EX_CLIENTEDGE);

        HWND window_handle = CreateWindowExA(WS_EX_CLIENTEDGE, "ARCADE", "Arcade v0.0",
		WS_OVERLAPPEDWINDOW | WS_THICKFRAME | WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT,
	        window_rect.right - window_rect.left, window_rect.bottom - window_rect.top, 0, 0,
		dll_name, 0);

	if (window_handle == 0)
		OutputDebugStringA("Window Creation Failed!");

	HDC window_device_context = GetDC(window_handle);
	if (window_device_context == 0)
		("Obtaining Device Context Failed!");

	win32_opengl_init(window_device_context);

	LARGE_INTEGER cpu_freq_result;
	QueryPerformanceFrequency(&cpu_freq_result);
	int64 cpu_freq = cpu_freq_result.QuadPart;

	ShowWindow(window_handle, display_flags);
	MSG msg = {};
	int32 full_of_life = program_start_up(&game_state);

	LARGE_INTEGER last_counter;
	QueryPerformanceCounter(&last_counter);
	while ((msg.message != WM_QUIT) && full_of_life)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	  	{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
	  	}
	 	full_of_life = program_run_loop();

	  if (!SwapBuffers(window_device_context))
	    OutputDebugStringA("Swapping Buffers Failed!");

	  LARGE_INTEGER end_counter;
	  QueryPerformanceCounter(&end_counter);

	  int64 counter_elapsed = end_counter.QuadPart - last_counter.QuadPart;
	  float64 ms_per_frame = (1000.0f *(float64)counter_elapsed) / (float64)cpu_freq;
	  float64 fps = (float64)cpu_freq / (float64)counter_elapsed;
	}

#ifdef RENDER_OPENGL
	if (opengl_context)
		wglDeleteContext(opengl_context);
#endif // RENDER_OPENGL
	return msg.message;
}
