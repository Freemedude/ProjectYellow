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
    m_target = target;
    m_count = count;

    glGenBuffers(1, &m_id);
    Bind();

    SetOpenGlLabel(GL_BUFFER, m_id, label);

    std::string lab = GetOpenGlLabel(GL_BUFFER, m_id);

    glBufferData(m_target, size * m_count, data, GL_STATIC_DRAW);
}

void GpuBuffer::Bind() const
{
    glBindBuffer(m_target, m_id);
}

void GpuBuffer::Unbind() const
{
    glBindBuffer(m_target, 0);
}

uint GpuBuffer::Count()
{
    return m_count;
}

