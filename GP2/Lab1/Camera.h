#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Camera
{
public:
	Camera()
	{
	}

	void initCamera(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip)
	{
		this->pos = pos;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, nearClip, farClip);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(pos, pos + forward, up);
	}

	void MoveForward(float amt)
	{
		pos += forward * amt;
	}

	void MoveLeft(float amt)
	{
		pos += glm::cross(up, forward) * amt;
	}

	void Pitch(float angle)
	{
		glm::vec3 right = glm::normalize(glm::cross(up, forward));

		forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
		up = glm::normalize(glm::cross(forward, right));
	}

	void TurnLeft(float angle)
	{
		static const glm::vec3 _up(0.0f, 1.0f, 0.0f);

		glm::mat4 rotation = glm::rotate(angle, _up);

		forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
		up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
	}

	glm::vec3 GetPosition()
	{
		return pos;
	}

protected:
private:
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
};

