#pragma once

#include "glad/glad.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class Shader
{
public:
  unsigned int ID; //shader id 
  

  //shader 
  Shader(const char* VertexPath, const char* FragPath); //frag masters lol
  
  //use the shaders
  void use();

  void setBool(const std::string &name, bool val) const;
  void setInt(const std::string &name, int val) const;
  void setFloat(const std::string &name, float val) const;
  
};


Shader::Shader(const char* VertexPath, const char* FragmentPath)
{ 
  //get the shadrs
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  //if the files loaded corectly
  
  vShaderFile.exceptions(std::ifstream::failbit| std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit| std::ifstream::badbit);
  try
  {
    // open files
    vShaderFile.open(VertexPath);
    fShaderFile.open(FragmentPath);
    if (!vShaderFile.is_open() || !fShaderFile.is_open())
    {
      std::cout<<"Unable to open shader files.\n";
    };

    std::stringstream vShaderStream,  fShaderStream;
    //read files
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    //close files
    vShaderFile.close();
    fShaderFile.close();
    //convert stream to string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
    if (vertexCode.empty() || fragmentCode.empty())
    {
      std::cout<< "Shader files are empty.\n";
    };
  }
  catch(std::ifstream::failure e)
  {
      std::cout<< "ERROR::SHADER:FILE_NOT_SUCCESFULLY_READ" <<'\n';
  }
  const char* vShaderCode = vertexCode.c_str();
  const char* fShaderCode = fragmentCode.c_str();
 //compile the shaders damit
  unsigned int vertex, fragment;
  int success;
  char infoLog[512];

  //vertex shader
  vertex =glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  //print errors ye
  glGetShaderiv(vertex,GL_COMPILE_STATUS, &success);
  if(!success)
  {
      glGetShaderInfoLog(vertex,512,NULL,infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog <<'\n';

  };
  
  //fragment shader
  fragment =glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  //print errors ye
  glGetShaderiv(fragment,GL_COMPILE_STATUS, &success);
  if(!success)
  {
      glGetShaderInfoLog(fragment,512,NULL,infoLog);
      std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog <<'\n';

  };
  
  // shader program
  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);

  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if(!success)
  {

    glGetProgramInfoLog(ID,512,NULL,infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" <<infoLog<<'\n';
  }


  //destroy shaders
  glDeleteShader(vertex);
  glDeleteShader(fragment);

};

void Shader::use()
{
    glUseProgram(ID);
};

void Shader::setBool(const std::string &name, bool val) const
{
   glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)val); 
};

void Shader::setInt(const std::string &name, int val) const
{
   glUniform1i(glGetUniformLocation(ID, name.c_str()), val); 
};

void Shader::setFloat(const std::string &name, float val) const
{
   glUniform1f(glGetUniformLocation(ID, name.c_str()), val); 
};


