#pragma once 

#include "glad/glad.h"

class VBO
{
    public:
      GLuint ID;
      VBO(float* vertices, GLsizeiptr size);

      void Bind();
      void Unbind();
      void Delete();
};

VBO::VBO(float* vertices, GLsizeiptr size)
{
  glGenBuffers(1,&ID); 
  glBindBuffer(GL_ARRAY_BUFFER,ID);   
  glBufferData(GL_ARRAY_BUFFER,size,vertices,GL_STATIC_DRAW);  

};

void VBO::Bind()
{ 
  glBindBuffer(GL_ARRAY_BUFFER,ID);   
};
void VBO::Unbind()
{ 
  glBindBuffer(GL_ARRAY_BUFFER,0);   
};
void VBO::Delete()
{ 
  glDeleteBuffers(1,&ID);   
};
