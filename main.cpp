#define STB_IMAGE_IMPLEMENTATION
//cpp libs
#include <iostream>
//opengl
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "include/textures/stb_image.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"
//imgui
#include "include/imgui/imgui.h"
#include "include/imgui/imgui_impl_glfw.h"
#include "include/imgui/imgui_impl_opengl3.h"
//my stuff
#include "include/shader/shader.h"
#include "include/textures/texture.h"
#include "include/objects/VAO.h"
#include "include/objects/VBO.h"
#include "include/objects/EBO.h"

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

  glEnable(GL_DEPTH_TEST);

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
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
  };

  Shader shader("shader/shader.vs","shader/shader.fs"); 

  Texture Wall("./wall.jpg",GL_TEXTURE_2D,GL_TEXTURE0,GL_RGB,GL_UNSIGNED_BYTE);
  Wall.textUnit(shader, "tex0" ,0);

  VAO VAO1;
  VAO1.Bind();

  VBO VBO1(vertices, sizeof(vertices));

  // position attribute
  VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
  // uv cords attribute
  VAO1.LinkAttrib(VBO1, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3*sizeof(float)));
  
  VAO1.Unbind();
  VBO1.Unbind();

  
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Wall.Bind();

    shader.use();

    glm::mat4 view          = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 projection    = glm::mat4(1.0f);

    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGTHT, 0.1f, 100.0f);
    view       = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    shader.setFloat("Time",(float)glfwGetTime());
    
    shader.setMat4("projection",projection);
    shader.setMat4("view",view);

    VAO1.Bind();
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime()*glm::radians(50.0f), glm::vec3(1.0f, 0.3f, 0.5f)); 
    shader.setMat4("model", model);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    //swap the rendering bufferd and get io
    glfwSwapBuffers(window);
    glfwPollEvents();    
  };
  Wall.Delete();
  VAO1.Delete();
  VBO1.Delete();

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


