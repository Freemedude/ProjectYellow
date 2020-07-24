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
        mat->Init(color, pipeline, nullptr);
        m_materials.push_back(mat);
    }

    // Floor
    auto pQuad = Mesh::make_quad();
    m_meshes.push_back(pQuad);


    auto pFloor = std::make_shared<Model>();
    pFloor->Init(pQuad, m_materials[matDist(rng)]);

    pFloor->Position().y = -5;
    pFloor->Rotation().x = -glm::radians(90.0f);
    pFloor->Scale().x = 25;
    pFloor->Scale().y = 25;
    m_models.push_back(pFloor);

    // Cubes
    auto pCube = Mesh::make_cube();
    m_meshes.push_back(pCube);

    // Debug cube
    auto cubeMaterial = std::make_shared<Material>();
    m_materials.push_back(cubeMaterial);
    cubeMaterial->Init({1, 1, 0, 1}, pipeline, nullptr);

    auto debugCube = std::make_shared<Model>();
    m_models.push_back(debugCube);
    debugCube->Init(pCube, cubeMaterial);
    debugCube->Scale() = {5, 5, 5};

    std::uniform_real_distribution<float> positionDist(-50.0f, 50.0);
    std::uniform_real_distribution<float> positionYDist(0.0f, 20.0);
    std::uniform_real_distribution<float> rotationDist(-20.0f, 20.0);
    std::uniform_real_distribution<float> scaleDist(0.1f, 1.5f);

    int numCubes = 100;

    for (int i = 0; i < numCubes; i++)
    {
        auto model = std::make_shared<Model>();
        model->Init(pCube, m_materials[matDist(rng)]);

        model->Position().x = positionDist(rng);
        model->Position().y = positionYDist(rng);
        model->Position().z = positionDist(rng);

        model->Rotation().x = rotationDist(rng);
        model->Rotation().y = rotationDist(rng);
        model->Rotation().z = rotationDist(rng);

        model->Scale().x = scaleDist(rng);
        model->Scale().y = scaleDist(rng);
        model->Scale().z = scaleDist(rng);
        m_models.push_back(model);
    }
}

std::vector<std::shared_ptr<Model>> &Scene::Models()
{
    return m_models;
}
