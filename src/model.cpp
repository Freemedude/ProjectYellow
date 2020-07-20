//
// @author freemedude
// @date 2020-07-19
// @brief 
//

#include "model.hpp"

void Model::Init(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
{
    m_mesh = mesh;
    m_material = material;
}

Transform &Model::GetTransform()
{
    return m_transform;
}

std::shared_ptr<Material> Model::GetMaterial()
{
    return m_material;
}


std::shared_ptr<Mesh> Model::GetMesh()
{
    return m_mesh;
}

