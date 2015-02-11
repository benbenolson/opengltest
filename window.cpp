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
    fprintf(stderr, "OPENGL ERROR: %s\n", message.c_str());
  }
}

GLFWwindow * Window::get() const
{
  return window;
}

Window::Window()
{
  window = startGLFW();
  startGLEW();
}

Window::~Window()
{
  glfwDestroyWindow(window);
  glfwTerminate();
}

GLFWwindow * Window::startGLFW()
{
  // Initialize GLFW
  glfwInit();

  // Set some window options
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  // Get the maximum screen resolution
  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode *mode = glfwGetVideoMode(monitor);

  // Create the window and OpenGL context
  GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "War", glfwGetPrimaryMonitor(), NULL);
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
