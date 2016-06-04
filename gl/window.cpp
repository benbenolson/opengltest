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
    width = mode->height - 100;
    height = mode->height - 100;
  }

  // Create the window and OpenGL context
  glOrtho(0.0f, width, height, 0.0f, 0.0f, 1.0f);
  GLFWwindow* window = glfwCreateWindow(width, height, "War", NULL, NULL);
  glfwMakeContextCurrent(window);

  //glMatrixMode(GL_PROJECTION);
  //glLoadIdentity();
  //glViewport(0, 0, width, height);

  return window;
}

void Window::startGLEW()
{
  glewExperimental = GL_TRUE;
  glewInit();
}

void Window::handle_keys()
{
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

void Window::clear_window()
{
  // Clear the screen
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Window::post_draw()
{
  checkErrors();
  glfwSwapBuffers(window);
  glfwPollEvents();
}

bool Window::should_close()
{
  return glfwWindowShouldClose(window);
}
