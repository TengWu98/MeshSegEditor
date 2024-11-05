﻿#include "Camera.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

Camera::Camera(glm::vec3 InPosition, glm::vec3 InWorldUp, glm::vec3 InTarget, float InFieldOfView, float InNearClip, float InFarClip) :
    Position(InPosition), WorldUp(InWorldUp), Front(glm::normalize(InTarget - Position)),
    FieldOfView(InFieldOfView), NearClip(InNearClip), FarClip(InFarClip)
{
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}

Camera::Camera(glm::vec3 InPosition, glm::vec3 InWorldUp, float InYaw, float InPitch, float InFieldOfView, float InNearClip, float InFarClip) :
    Position(InPosition), WorldUp(InWorldUp), Yaw(InYaw), Pitch(InPitch),
    FieldOfView(InFieldOfView), NearClip(InNearClip), FarClip(InFarClip)
{
    Front.x = glm::cos(Pitch)*glm::sin(Yaw);
    Front.y = glm::sin(Pitch);
    Front.z = glm::cos(Pitch)*glm::cos(Yaw);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, WorldUp);
}

glm::mat4 Camera::GetProjectionMatrix(float AspectRatio)
{
    return glm::perspective(glm::radians(FieldOfView), AspectRatio, NearClip, FarClip);
}

glm::mat4 Camera::GetViewProjectionMatrix(float AspectRatio)
{
    return GetProjectionMatrix(AspectRatio) * GetViewMatrix();
}

glm::mat4 Camera::GetInvViewProjectionMatrix(float AspectRatio)
{
    return glm::inverse(GetViewProjectionMatrix(AspectRatio));
}

float Camera::GetDistance() const
{
    return glm::distance(Position, Position + Front);
}

void Camera::SetPositionFromView(const glm::mat4& ViewMatrix)
{
    Position = glm::inverse(ViewMatrix)[3];
    bIsMoving = false;
}

void Camera::SetTargetDistance(float Distance)
{
    TargetDistance = Distance;
    bIsMoving = true;
}

void Camera::Tick()
{
    if(!bIsMoving)
    {
        return;
    }

    const auto Distance = GetDistance();
    if(std::abs(Distance - TargetDistance) < 0.01f)
    {
        bIsMoving = false;
        SetDistance(TargetDistance);
    }
    else
    {
        SetDistance(glm::mix(Distance, TargetDistance, MovementSpeed));
    }
}

void Camera::SetDistance(float Distance)
{
    Position += Front + glm::normalize(Front) * Distance;
}
