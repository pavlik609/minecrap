#pragma once
#include "../glad/glad.h"
#include "VBO.h"

class VAO
{
    public:
      GLuint ID; 
      VAO();
      
      void LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride,void* offset);
      void Bind();
      void Unbind();
      void Delete();

};
VAO::VAO()
{
    glGenVertexArrays(1,&ID);
};
void VAO::LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride,void* offset)
{
  VBO.Bind();
  glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride ,offset);
  glEnableVertexAttribArray(layout);
  VBO.Unbind();
};
void VAO::Bind()
{
  glBindVertexArray(ID);
};
void VAO::Unbind()
{
  glBindVertexArray(0);
};
void VAO::Delete()
{
  glDeleteVertexArrays(1, &ID);
};
