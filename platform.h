#if !defined(PLATFORM_H)
#define PLATFORM_H

#define FONT_THIN             100
#define FONT_EXTRALIGHT       200
#define FONT_LIGHT            300
#define FONT_NORMAL           400
#define FONT_MEDIUM           500
#define FONT_SEMIBOLD         600
#define FONT_BOLD             700
#define FONT_EXTRABOLD        800
#define FONT_HEAVY            900

struct File
{
  byte* data;
  uint32 byte_size;
};

struct Font
{
  char* name;
  int32 height;
  int32 weight;
  int32 glyph_width[95]{};
  int32 glyph_height[95]{};
  byte* glyph_data[95]{};
  uint32 texture_id[95]{};
};

struct ButtonState
{
  int8 is_down;
  int8 was_down;
};

struct Mouse
{
  uint16 left_down;
  uint16 right_down;
  
};

File
platform_read_file(char* file_path);

char 
platform_create_font(char* file_name, char* font_name, Font* font_object, int desired_height, int desired_weight);

void
platform_delete_font(Font* font_object);

void // NOTE: returned value is relative to 0,0 being the top left corner of the drawable window.
platform_get_cursor_position(float64 *x, float64 *y); 

#endif
