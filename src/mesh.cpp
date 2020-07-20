//
// @author freemedude
// @date 2020-07-19
// @brief 
//

#include "mesh.hpp"

#include <iostream>

Mesh::~Mesh()
{
    std::cout << "Destroyed Mesh" << std::endl;
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

    // Position
    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);
    // Color
    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (void *) offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

}


void Mesh::Bind()
{
    glBindVertexArray(m_id);
    m_iBuffer.Bind();
}

i32 Mesh::Count()
{
    return m_iBuffer.Count();
}
