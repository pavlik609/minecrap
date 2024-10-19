#define STB_IMAGE_IMPLEMENTATION
//cpp libs
#include <iostream>
//opengl
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "include/image_loader/stb_image.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"
//imgui
#include "include/imgui/imgui.h"
#include "include/imgui/imgui_impl_glfw.h"
#include "include/imgui/imgui_impl_opengl3.h"
//my stuff
#include "include/shader/shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGTHT = 600;

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGTHT, "opengl game", NULL, NULL);
  if (window == NULL)
  {
    std::cout <<"GLFW FAILED TO CREATE A WINDOW \n"; 
    glfwTerminate();
    return -1;

  };

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout<< "GLAD FAILD TO INIT \n";
    return -1;
  };
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
  ImGui_ImplOpenGL3_Init();
  
  //the mesh
  float vertices[] = {
    // positions         // uv cords
     0.5f, -0.5f, 0.0f,  0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f,    // bottom left
     0.0f,  0.5f, 0.0f,  0.5f, 1.0f    // top 
  };
  //pls less buffers why 3 ???
  unsigned int VBO, VAO;
  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);  

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // uv cords attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER,0);

  glBindVertexArray(0);
   
  Shader shader("shader/shader.vs","shader/shader.fs"); 

 unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);  
  
  int width, height, nrChannels;
  unsigned char *data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);

  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cout << "Failed to load texture" << std::endl;
  };
  stbi_image_free(data);
  //the LOOP
  while(!glfwWindowShouldClose(window))
  {
    //input
    processInput(window);
    // test 
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow(); // Show demo window! :)
    //render
    glClearColor(0.1f,0.2f,0.5f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();
    shader.setFloat("Time",(float)glfwGetTime());
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0,3);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    //swap the rendering bufferd and get io
    glfwSwapBuffers(window);
    glfwPollEvents();    
  };

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwTerminate();
  return 0;
};

void processInput(GLFWwindow *window)
{
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
};


