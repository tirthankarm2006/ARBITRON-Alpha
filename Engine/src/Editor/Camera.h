#pragma once

#include "EditorLog.h"

namespace ARB{
	class Camera
	{
	public:
		Camera(glm::vec3 position, glm::vec3 up, unsigned int Scr_width, unsigned int Scr_height);
		float deltaTime;
		void KeyInputProcess(GLFWwindow* window, float deltatime);
		void MouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
		void MouseScrollCallback(GLFWwindow* window, double ypos);
	    glm::mat4 GetViewMatrix() { return glm::lookAt(position, position+front, up); }
		glm::mat4 GetPerspectiveMatrix() { return glm::perspective(glm::radians(zoom), (float)scr_width/ scr_height, 0.1f, 500.0f); }
		glm::vec3 position;
	private:
		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 right;
		double yaw;
		double pitch;

		std::shared_ptr<Editor::Log> cameraLogger;

		unsigned int scr_width, scr_height;

		float movementSpeed;
		float mouseSentivity;
		float zoom;

		double lastX, lastY;

		void updateCameraVectors();
	};
}

