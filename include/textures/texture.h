#pragma once

#include "glad/glad.h"
#include "../image_loader/stb_image.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class Texture
{
  public:
  int width, heigth, nrChannels;
  unsigned char *image_data; //the textures texels why char tho ?
  
  Texture(const char* TexturePath);
};
