//
// @author freemedude
// @date 2020-07-19
// @brief 
//

#include "mesh.hpp"

#include <iostream>

Mesh::~Mesh()
{
    std::cout << "Destroyed Mesh " << std::endl;
    glDeleteVertexArrays(1, &m_id);
}

void Mesh::Init(std::vector<Vertex> &verts, std::vector<Index> &indices)
{

    glGenVertexArrays(1, &m_id);

    m_vBuffer.Init(
        "Vertex Buffer",
        GL_ARRAY_BUFFER,
        verts.data(),
        verts.size(),
        sizeof(verts[0]));

    m_iBuffer.Init(
        "Index Buffer",
        GL_ELEMENT_ARRAY_BUFFER,
        indices.data(),
        indices.size(),
        sizeof(indices[0]));

    Bind();

    i64 offset = 0;
    int index = 0;

    auto addAttribute = [&](uint type, int count, bool normalize = false)
    {
        int typeSize = 0;
        if(type == GL_FLOAT)
        {
            typeSize = 4;
        } else{
            throw std::invalid_argument("Unknown type passed to addAttribute");
        }

        glVertexAttribPointer(index, count, type, normalize, sizeof(Vertex), (void*) offset);
        glEnableVertexAttribArray(index);
        offset += typeSize * count;
        index++;
    };

    // Position
    addAttribute(GL_FLOAT, 3);
    // Normal
    addAttribute(GL_FLOAT, 3);
    // Uv
    addAttribute(GL_FLOAT, 2);

}


void Mesh::Bind()
{
    glBindVertexArray(m_id);
    m_iBuffer.Bind();
}

u64 Mesh::Count()
{
    return m_iBuffer.mCount;
}
