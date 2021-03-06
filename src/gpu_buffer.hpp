//
// @author freemedude
// @date 2020-07-19
// @brief
//
#pragma once

#include <glad/glad.h>
#include <string>

#include "integers.h"


class GpuBuffer
{
public:
    GpuBuffer() = default;
    ~GpuBuffer();

    void Init(const std::string &label, uint target, void* data, u64 count, u64 size);
    void Bind() const;

    u64 mCount = 0;
private:
    uint m_id = 0;
    uint m_target = 0;

};