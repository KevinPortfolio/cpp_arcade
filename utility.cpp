
bool
str_compare_null_terminated(char* str_a, char* str_b)
{  
  if (!str_a && !str_b)
    return 1;
  if (!str_a || !str_b)
    return 0;
  
  while (*str_a && *str_b)
  {
    if (*(str_a++) != *(str_b++))
      return 0;
  }
  
  if (!(*str_a) && !(*str_b))
    return 1;
  return 0;
}

File
parse_glsl_vertice(File shader_file)
{
  File result = {};
  byte* result_itr = result.data;
  byte* file_itr = shader_file.data;

  unsigned int begin_file_index = 0;
  unsigned int end_file_index = 0;
  unsigned int data_index = 0;
  unsigned int label_index = 0;
  char label[256] = {};
  bool extraction = false;
  
  if (shader_file.data)
  {
    while(data_index < shader_file.byte_size)
    { // TODO: Pointer or byte walkthrough?
      if (file_itr[data_index] == '@')
      {
	bool32 label_complete = false;
	data_index++;
	
	while ((data_index < shader_file.byte_size) && (label_complete == false))
	{
	  if (file_itr[data_index] == '@')
	  {
	    label_complete = true;
	    data_index++;
	  }
	  else
	    label[label_index++] = file_itr[data_index++];
	  
	}
	if (str_compare_null_terminated(label, "vertex"))
	{
	  extraction = true;
	  begin_file_index = data_index;
	}
	else if (str_compare_null_terminated(label, "stop"))
	{
	  if (extraction == true)
	  {
	    extraction = false;
	    end_file_index = data_index - 6; // NOTE: 6 = @ + stop + @
	    data_index = shader_file.byte_size;
	  }
	}

	for (unsigned int i = 0; i < label_index; i++)
	  label[i] = 0;
	label_index = 0;
      }
      else if (extraction == true)
      {
	result.byte_size++;
	data_index++;
      }
      else
      {
	data_index++;
      }
    }
    
    if (result.byte_size)
    {
      result.data = new byte[result.byte_size];
      for (unsigned int i = 0; i < result.byte_size; i++)
	result.data[i] = file_itr[i + begin_file_index];
    }
  }
  
  return result;
}

File
parse_glsl_fragment(File shader_file)
{
  File result = {};
  byte* result_itr = result.data;
  byte* file_itr = shader_file.data;
  
  unsigned int data_index = 0;
  unsigned int label_index = 0;
  unsigned int begin_file_index = 0;
  unsigned int end_file_index = 0;
  char label[256] = {};
  bool extraction = false;
  if (shader_file.data)
  {
    while(data_index < shader_file.byte_size)
    {
      
      if (file_itr[data_index] == '@')
      {
	bool32 label_complete = false;
	data_index++;
	while ((data_index < shader_file.byte_size) && (label_complete == false))
	{
	  if (file_itr[data_index] == '@')
	  {
	    label_complete = true;
	    data_index++;
	  }
	  else
	    label[label_index++] = file_itr[data_index++];
	  
	}
	if (str_compare_null_terminated(label, "fragment"))
	{
	  extraction = true;
	  begin_file_index = data_index;
	}
	else if (str_compare_null_terminated(label, "stop"))
	{
	  if (extraction == true)
	  {
	    extraction = false;
	    end_file_index = data_index - 6; // NOTE: 6 = @ + stop + @
	    data_index = shader_file.byte_size;
	  }
	}

	for (unsigned int i = 0; i < label_index; i++)
	  label[i] = 0;
	label_index = 0;
      }
      else if (extraction == true)
      {
	result.byte_size++;
	data_index++;
      }
      else
      {
	data_index++;
      }
    }
    
    if (result.byte_size)
    {
      result.data = new byte[result.byte_size];
      for (unsigned int i = 0; i < result.byte_size; i++)
	result.data[i] = file_itr[i + begin_file_index];
      
    }
  }
   return result;
}
