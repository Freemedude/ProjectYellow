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
private:
    std::shared_ptr<Mesh> m_mesh {};
    std::shared_ptr<Material> m_material {};
    Transform m_transform {};

public:
    Model() = default;

    void Init(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);

    Transform &GetTransform();
    std::shared_ptr<Material> GetMaterial();
    std::shared_ptr<Mesh> GetMesh();
};


#endif //PROJECT_YELLOW_MODEL_HPP
