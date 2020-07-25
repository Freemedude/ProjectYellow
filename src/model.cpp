//
// @author freemedude
// @date 2020-07-19
// @brief 
//

#include "model.hpp"

void Model::Init(const std::string &name, std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
{
    m_name = name;
    m_mesh = mesh;
    m_material = material;
}

glm::vec3 &Model::Position()
{
    return m_transform.position;
}

glm::vec3 &Model::Rotation()
{
    return m_transform.rotation;
}
glm::vec3 &Model::Scale()
{
    return m_transform.scale;
}

