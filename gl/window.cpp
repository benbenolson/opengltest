#include "window.hpp"
#include <string>
#include <cstdio>

void Window::checkErrors()
{
  std::string message;
  GLenum error = glGetError();
  switch(error) {
    case GL_INVALID_ENUM: message = "Invalid enum."; break;
    case GL_INVALID_VALUE: message = "Invalid value."; break;
    case GL_INVALID_OPERATION: message = "Invalid operation."; break;
    case GL_INVALID_FRAMEBUFFER_OPERATION: message = "Invalid framebuffer operation."; break;
    case GL_OUT_OF_MEMORY: message = "Out of memory."; break;
    case GL_STACK_UNDERFLOW: message = "Stack underflow."; break;
    case GL_STACK_OVERFLOW: message = "Stack overflow."; break;
  }
  if(error) {
    fprintf(stderr, "WINDOW ERROR: %s\n", message.c_str());
  }
}

GLFWwindow * Window::get() const
{
  return window;
}

Window::Window()
{
  window = startGLFW(0, 0);
  startGLEW();
  checkErrors();
}

Window::Window(GLint width, GLint height)
{
  window = startGLFW(width, height);
  startGLEW();
  checkErrors();
}

Window::~Window()
{
  glfwDestroyWindow(window);
  glfwTerminate();
}

GLFWwindow * Window::startGLFW(GLint width, GLint height)
{
  // Initialize GLFW
  glfwInit();

  // Set some window options
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  
  if((width == 0) || (height == 0)) {
    // Get the maximum square screen resolution
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    width = mode->height;
    height = mode->height;
  }

  // Create the window and OpenGL context
  GLFWwindow* window = glfwCreateWindow(width, height, "War", NULL, NULL);
  glfwMakeContextCurrent(window);

  return window;
}

void Window::startGLEW()
{
  glewExperimental = GL_TRUE;
  glewInit();
}

void Window::eventLoop(void (*draw)(State *), State *state)
{
  while(!glfwWindowShouldClose(window)) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }

    // Clear the screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    draw(state);
    checkErrors();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}