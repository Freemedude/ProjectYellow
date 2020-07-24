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
private:
    std::vector<std::shared_ptr<Model>> m_models;
    std::vector<std::shared_ptr<Mesh>> m_meshes;
    std::vector<std::shared_ptr<Material>> m_materials;
    std::vector<std::shared_ptr<RasterPipeline>> m_pipelines;
    std::vector<std::shared_ptr<Texture>> m_textures;

public:
    Scene() = default;
    void Init();
    void TestScene();
    std::vector<std::shared_ptr<Model>> &Models();
private:
};


#endif //PROJECT_YELLOW_SCENE_HPP
