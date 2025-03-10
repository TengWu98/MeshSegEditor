﻿#pragma once

#include "pch.h"

LINK_EDITOR_NAMESPACE_BEGIN

class UniformBuffer
{
public:
    UniformBuffer(uint32_t Size, uint32_t Binding);
    ~UniformBuffer();

    void SetData(const void* Data, uint32_t Size, uint32_t Offset = 0);
    
private:
    uint32_t RendererID;
};

LINK_EDITOR_NAMESPACE_END
