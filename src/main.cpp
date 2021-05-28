#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <chrono>
#include <memory>

#include "window.hpp"
#include "camera.hpp"
#include "pointCloud.hpp"
#include "pointCloudRenderer.hpp"

void onResize(GLFWwindow* window, int width, int height)
{
  Matrix* projectionMatrix = (Matrix*)glfwGetWindowUserPointer(window);

  const float aspectRatio = static_cast<float>(width) / height;
  *projectionMatrix = Matrix::initPerspective(M_PI / 2.0, aspectRatio, 0.1f, 1000.0f);

  glViewport(0, 0, width, height);
}

void input(Window& window, Camera& camera)
{
  const float movementSpeed = 0.06f;
  const float rotationSpeed = 0.02f;
  
  if(glfwGetKey(window.getWindowPtr(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    window.close();

  if(glfwGetKey(window.getWindowPtr(), GLFW_KEY_W) == GLFW_PRESS)
    camera.move(Camera::CameraDirection::Forward, movementSpeed);
  else if(glfwGetKey(window.getWindowPtr(), GLFW_KEY_S) == GLFW_PRESS)
    camera.move(Camera::CameraDirection::Back, movementSpeed);
  else if(glfwGetKey(window.getWindowPtr(), GLFW_KEY_A) == GLFW_PRESS)
    camera.move(Camera::CameraDirection::Left, movementSpeed);
  else if(glfwGetKey(window.getWindowPtr(), GLFW_KEY_D) == GLFW_PRESS)
    camera.move(Camera::CameraDirection::Right, movementSpeed);
  
  if(glfwGetKey(window.getWindowPtr(), GLFW_KEY_UP) == GLFW_PRESS)
    camera.rotateX(rotationSpeed);
  else if(glfwGetKey(window.getWindowPtr(), GLFW_KEY_DOWN) == GLFW_PRESS)
    camera.rotateX(-rotationSpeed);
  else if(glfwGetKey(window.getWindowPtr(), GLFW_KEY_LEFT) == GLFW_PRESS)
    camera.rotateY(rotationSpeed);
  else if(glfwGetKey(window.getWindowPtr(), GLFW_KEY_RIGHT) == GLFW_PRESS)
    camera.rotateY(-rotationSpeed);
}

int main()
{
  const unsigned int NUM_FRAMES = 2101;

  std::cout << "Loading data...\n";
  const auto frames = PointCloud::loadFrames("./data", NUM_FRAMES);
  std::cout << "Done!\n";

  Window window{"Point Cloud", 800, 600};
  window.setResizeCallback(onResize);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CW);
  glCullFace(GL_BACK);

  glViewport(0, 0, window.getWidth(), window.getHeight());

  try
  {
    Camera camera{Vector3{2, 140, -5}, Vector3{1, 0, -1}, Vector3{0, -1, 0}};
        
    const float aspectRatio = (float)window.getWidth() / window.getHeight();
    auto projectionMatrix = std::make_unique<Matrix>();
    *projectionMatrix = Matrix::initPerspective(M_PI / 2.0, aspectRatio, 0.1f, 1000.0f);
    glfwSetWindowUserPointer(window.getWindowPtr(), projectionMatrix.get());

    Matrix modelMatrix = Matrix::initIdentity();
    PointCloudRenderer pointCloudRenderer{};

    auto then = std::chrono::steady_clock::now();
    unsigned int frame = 0;

    while(window.isRunning())
    {
      input(window, camera);
      
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      pointCloudRenderer.setPointCloud(frames[frame]);
      pointCloudRenderer.render(camera, *projectionMatrix, modelMatrix);

      window.update();

      const auto now = std::chrono::steady_clock::now();
      std::chrono::duration<float> delta = now - then;
      frame = (unsigned int)std::floor(30 * delta.count()) % NUM_FRAMES;
    }
  }
  catch(std::runtime_error& ex)
  {
    std::cout << ex.what() << "\n";
  }

  return 0;
}