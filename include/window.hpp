#pragma once

class GLFWwindow;

class Window
{
public:
  Window(const char* title, unsigned int width, unsigned int height);
  ~Window();

  void update();
  void close();
  void toggleFullscreen();
  void setResizeCallback(void(*cb)(GLFWwindow*, int, int));

  GLFWwindow* getWindowPtr();

  unsigned int getWidth() const;
  unsigned int getHeight() const;
  bool isRunning() const;
private:
  GLFWwindow* window_;
  unsigned int width_;
  unsigned int height_;
  bool running_;
};