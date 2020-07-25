//
// @author freemedude
// @date 2020-07-19
// @brief 
//

#ifndef PROJECT_YELLOW_MODEL_HPP
#define PROJECT_YELLOW_MODEL_HPP

#include <memory>

#include "material.hpp"
#include "transform.hpp"
#include "mesh.hpp"

class Model
{
public:
    std::string m_name;
    std::shared_ptr<Mesh> m_mesh{};
    std::shared_ptr<Material> m_material{};
    Transform m_transform{};

    Model() = default;

    void Init(const std::string &name, std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);

    glm::vec3 &Position();

    glm::vec3 &Rotation();

    glm::vec3 &Scale();
};


#endif //PROJECT_YELLOW_MODEL_HPP
