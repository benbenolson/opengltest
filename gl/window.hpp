#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include "opengl.hpp"
#include "state.hpp"

class Window
{
  private:
    GLFWwindow *window;
    GLFWwindow *startGLFW(GLint width, GLint height);
    void checkErrors(std::string loc);
    void startGLEW();
  public:
    Window();
    Window(GLint width, GLint height);
    ~Window();
    GLFWwindow *get() const;
    void handle_keys();
    void clear_window();
    void post_draw();
    bool should_close();
};

#endif
