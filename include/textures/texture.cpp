#include "texture.h"

Texture::Texture(const char* TexturePath,GLenum slot)
{
  int width, height, nrChannels;
  unsigned char *data = stbi_load(TexturePath, &width, &height, &nrChannels, 0);

  glGenTextures(1, &ID);
  glActiveTexture(slot);
  glBindTexture(GL_TEXTURE_2D, ID);

 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
  
  if (!data)
  {
    std::cout << "Failed to load texture" << std::endl;
  };

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
  glBindTexture(GL_TEXTURE_2D,0);


};

void Texture::Bind()
{
  glBindTexture(GL_TEXTURE_2D,ID);
};

void Texture::Unbind()
{
  glBindTexture(GL_TEXTURE_2D,0);
};

void Texture::Delete()
{
  glDeleteTextures(1,&ID);
};

