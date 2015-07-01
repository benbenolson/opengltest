#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include "opengl.hpp"
#include "state.hpp"

class Window
{
  private:
    GLFWwindow *window;
    GLFWwindow *startGLFW(GLint width, GLint height);
    void checkErrors();
    void startGLEW();
  public:
    Window();
    Window(GLint width, GLint height);
    ~Window();
    GLFWwindow *get() const;
    void eventLoop(void (*draw)(State *), State *state);
};

#endif
