﻿#pragma once

#include "pch.h"
#include "Codes/KeyCodes.h"
#include "Codes/MouseCodes.h"

struct GLFWwindow;

class Input
{
public:
    static bool IsKeyPressed(GLFWwindow* Window, KeyCode KeyCode);
    static bool IsMouseButtonPressed(GLFWwindow* Window, MouseCode Button);
    static glm::vec2 GetMousePosition(GLFWwindow* Window);
    static float GetMouseX(GLFWwindow* Window);
    static float GetMouseY(GLFWwindow* Window);
};
