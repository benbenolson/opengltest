#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include "opengl.hpp"
#include "state.hpp"

class Window
{
  private:
    GLFWwindow *window;
    GLFWwindow *startGLFW();
    void startGLEW();
    void checkErrors();
  public:
    Window();
    ~Window();
    GLFWwindow *get() const;
    void eventLoop(void (*draw)(State *), State *state);
};

#endif
