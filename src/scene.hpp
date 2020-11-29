//
// @author freemedude
// @date 2020-07-19
// @brief 
//

#ifndef PROJECT_YELLOW_SCENE_HPP
#define PROJECT_YELLOW_SCENE_HPP

#include <vector>
#include <memory>

#include "model.hpp"

class Scene
{
public:
    std::vector<std::shared_ptr<Model>> m_models;
    std::vector<std::shared_ptr<Mesh>> m_meshes;
    std::vector<std::shared_ptr<Material>> m_materials;
    std::vector<std::shared_ptr<ShaderProgram>> m_programs;
    std::vector<std::shared_ptr<Texture>> m_textures;

    Scene() = default;
    void Init();
    void TestScene();
private:
};


#endif //PROJECT_YELLOW_SCENE_HPP
