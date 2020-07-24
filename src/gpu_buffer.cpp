//
// @author freemedude
// @date 2020-07-19
// @brief
//

#include "gpu_buffer.hpp"

#include <iostream>

#include "opengl_helpers.hpp"

GpuBuffer::~GpuBuffer()
{
    std::cout << "Destroyed Buffer" << std::endl;
    glDeleteBuffers(1, &m_id);
}

void GpuBuffer::Init(const std::string &label, uint target, void *data, u64 count, u64 size)
{
    this->m_target = target;
    mCount = count;

    glGenBuffers(1, &m_id);
    Bind();

    SetOpenGlLabel(GL_BUFFER, m_id, label);

    std::string lab = GetOpenGlLabel(GL_BUFFER, m_id);

    glBufferData(target, size * count, data, GL_STATIC_DRAW);
}

void GpuBuffer::Bind() const
{
    glBindBuffer(m_target, m_id);
}


