#pragma once

#include "glad/glad.h"
#include "../shader/shader.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class Texture
{
  public:
  unsigned int ID;
  GLenum type;
  Texture(const char* TexturePath,GLenum textType, GLenum slot, GLenum format, GLenum pixelType);
  
  void textUnit(Shader shader, const char* uniform, GLuint unit);
  void Bind(); 
  void Unbind();
  void Delete();
};
Texture::Texture(const char* TexturePath,GLenum textType, GLenum slot, GLenum format, GLenum pixelType)
{
  type= textType;
  int width, height, nrChannels;
  unsigned char *data = stbi_load(TexturePath, &width, &height, &nrChannels, 0);

  glGenTextures(1, &ID);
  glActiveTexture(slot);
  glBindTexture(textType, ID);

 
  glTexParameteri(textType, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(textType, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  glTexParameteri(textType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(textType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
  
  if (!data)
  {
    std::cout << "Failed to load texture" << std::endl;
  };

  glTexImage2D(textType, 0, GL_RGBA, width, height, 0, format, pixelType, data);
  glGenerateMipmap(textType);

  stbi_image_free(data);
  glBindTexture(textType,0);

};
void Texture::textUnit(Shader shader, const char* uniform, GLuint unit)
{
    GLuint texUni = glGetUniformLocation(shader.ID,uniform);
    shader.use();
    glUniform1i(texUni,unit);
};
void Texture::Bind()
{
  glBindTexture(type,ID);
};

void Texture::Unbind()
{
  glBindTexture(type,0);
};

void Texture::Delete()
{
  glDeleteTextures(1,&ID);
};
