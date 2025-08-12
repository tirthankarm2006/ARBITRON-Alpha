#include "ARBpch.h"
#include "Camera.h"

namespace ARB {
#define YAW -90.0f
#define PITCH 0.0F
#define SPEED 2.5f
#define SENSITIVITY 0.1F
#define ZOOM_FOV 45.0f

	bool once = true;

	Camera::Camera(glm::vec3 position, glm::vec3 up, unsigned int Scr_width, unsigned int Scr_height) : mouseSentivity(SENSITIVITY), movementSpeed(SPEED), zoom(ZOOM_FOV), yaw(YAW), pitch(PITCH){
		cameraLogger = std::make_shared<Editor::Log>("Engine::Camera");
		this->position = position;
		this->up = up;
		scr_width = Scr_width;
		scr_height = Scr_height;
		updateCameraVectors();
	}

	void Camera::updateCameraVectors() {
		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		front = glm::normalize(direction);
		right = glm::normalize(glm::cross(front, up));
	}

	void Camera::KeyInputProcess(GLFWwindow* window, float deltatime) {

		float velocity = movementSpeed * deltatime;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			position += velocity * front;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			position -= velocity * front;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			position -= right * velocity;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			position += right * velocity;
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			position -= velocity * up;
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			position += velocity * up;
	}

	void Camera::MouseMoveCallback(GLFWwindow* window, double xpos, double ypos) {

		if (once) {
			lastX = xpos;
			lastY = ypos;
			once = false;
		}

			double xOffset = 0, yOffset = 0;
		if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {

			xOffset = xpos - lastX;
			yOffset = lastY - ypos;
		}

			lastX = xpos;
			lastY = ypos;

			xOffset *= mouseSentivity;
			yOffset *= mouseSentivity;

			yaw += xOffset;
			pitch += yOffset;

			if (pitch > 89.9f)
				pitch = 89.9f;
			if (pitch < -89.9f)
				pitch = -89.9f;

			updateCameraVectors();
	}

	void Camera::MouseScrollCallback(GLFWwindow* window, double yOffset) {
		if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
			zoom -= (float)yOffset;

			if (zoom < 1.0f)
				zoom = 1.0f;
			if (zoom > 60.0f)
				zoom = 60.0f;
		}
	}
}
