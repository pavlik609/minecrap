#pragma once 

#include "glad/glad.h"

class EBO
{
    public:
      GLuint ID;
      EBO(int* indices, GLsizeiptr size);

      void Bind();
      void Unbind();
      void Delete();
};

EBO::EBO(int* indices, GLsizeiptr size)
{
  glGenBuffers(1,&ID); 
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ID);   
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,size,indices,GL_STATIC_DRAW);  

};

void EBO::Bind()
{ 
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ID);   
};
void EBO::Unbind()
{ 
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);   
};
void EBO::Delete()
{ 
  glDeleteBuffers(1,&ID);   
};
