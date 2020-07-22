//
// @author freemedude
// @date 2020-07-19
// @brief 
//

#include "scene.hpp"
#include <random>

void Scene::Init()
{

}

void Scene::TestScene()
{
    std::random_device dev;
    std::mt19937 rng(dev());


    // Materials

    auto pipeline = std::make_shared<RasterPipeline>();
    pipeline->Init("shaders/Default.vert", "shaders/Default.frag");
    m_pipelines.push_back(pipeline);

    int numMats = 10;

    std::uniform_real_distribution<> colorDist(0, 1);
    std::uniform_int_distribution<> matDist(0, numMats - 1);

    for (int i = 0; i < numMats; i++)
    {
        auto mat = std::make_shared<Material>();
        glm::vec4 color{colorDist(rng), colorDist(rng), colorDist(rng), colorDist(rng)};
        mat->Init(color, pipeline);
        m_materials.push_back(mat);
    }

    // Floor
    auto pQuad = Mesh::make_quad();
    m_meshes.push_back(pQuad);


    auto pFloor = std::make_shared<Model>();
    pFloor->Init(pQuad, m_materials[matDist(rng)]);

    pFloor->GetTransform().position.y = -5;
    pFloor->GetTransform().rotation.x = -glm::radians(90.0);
    pFloor->GetTransform().scale.x = 25;
    pFloor->GetTransform().scale.y = 25;
    m_models.push_back(pFloor);

    // Cubes
    auto pCube = Mesh::make_cube();
    m_meshes.push_back(pCube);

    // Debug cube
    auto cubeMaterial = std::make_shared<Material>();
    m_materials.push_back(cubeMaterial);
    cubeMaterial->Init({1, 1, 0, 1}, pipeline);

    auto debugCube = std::make_shared<Model>();
    m_models.push_back(debugCube);
    debugCube->Init(pCube, cubeMaterial);
    debugCube->GetTransform().scale = {5, 5, 5};

    std::uniform_real_distribution<> positionDist(-50, 50);
    std::uniform_real_distribution<> positionYDist(0, 20);
    std::uniform_real_distribution<> rotationDist(-20, 20);
    std::uniform_real_distribution<> scaleDist(0.1, 1.5);

    int numCubes = 100;

    for (int i = 0; i < numCubes; i++)
    {
        auto model = std::make_shared<Model>();
        model->Init(pCube, m_materials[matDist(rng)]);

        Transform &transform = model->GetTransform();
        transform.position.x = positionDist(rng);
        transform.position.y = positionYDist(rng);
        transform.position.z = positionDist(rng);

        transform.rotation.y = rotationDist(rng);
        transform.rotation.y = rotationDist(rng);
        transform.rotation.z = rotationDist(rng);

        transform.scale.x = scaleDist(rng);
        transform.scale.z = scaleDist(rng);
        transform.scale.z = scaleDist(rng);
        m_models.push_back(model);
    }
}

std::vector<std::shared_ptr<Model>> &Scene::Models()
{
    return m_models;
}
