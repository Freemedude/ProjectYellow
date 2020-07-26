//
// @author freemedude
// @date 2020-07-19
// @brief 
//

#include "scene.hpp"

#include <string>
#include <random>

void Scene::Init()
{

}

template<typename T>
T Choose(std::vector<T> &v)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<> indexDist(0, v.size() - 1);
    int index = indexDist(rng);
    T result = v[index];
    return result;
}

void Scene::TestScene()
{
    std::random_device dev;
    std::mt19937 rng(dev());

    // Textures
    auto stickFigure = std::make_shared<Texture>();
    stickFigure->Init("Stick Figure", "images/cube_texture.png", 4);
    m_textures.push_back(stickFigure);

    auto testPng = std::make_shared<Texture>();
    testPng->Init("Test image", "images/test.png", 3);
    m_textures.push_back(testPng);

    // Materials
    auto pipeline = std::make_shared<RasterPipeline>();
    pipeline->Init("shaders/Default.vert", "shaders/Default.frag");
    m_pipelines.push_back(pipeline);

    int numMats = 20;

    std::uniform_real_distribution<> colorDist(0, 1);
    std::uniform_int_distribution<> matDist(0, numMats - 1);

    for (int i = 0; i < numMats; i++)
    {
        auto mat = std::make_shared<Material>();
        glm::vec4 color{colorDist(rng), colorDist(rng), colorDist(rng), colorDist(rng)};
        mat->Init("Material " + std::to_string(i), color, pipeline, stickFigure);
        m_materials.push_back(mat);
    }

    // Floor
    auto pQuad = Mesh::make_quad();
    m_meshes.push_back(pQuad);


    auto pFloor = std::make_shared<Model>();
    pFloor->Init("Floor", pQuad, m_materials[matDist(rng)]);

    pFloor->Position() = {0, -5, 0};
    pFloor->Rotation() = {-glm::radians(90.0f), 0, 0};
    pFloor->Scale() = {100, 100, 1};
    m_models.push_back(pFloor);

    // Cubes
    auto pCube = Mesh::make_cube();
    m_meshes.push_back(pCube);

    // Debug cube
    auto cubeMaterial = std::make_shared<Material>();
    m_materials.push_back(cubeMaterial);
    cubeMaterial->Init("Cube Material", {1, 1, 0, 1}, pipeline, testPng);

    auto debugCube = std::make_shared<Model>();
    m_models.push_back(debugCube);
    debugCube->Init("Debug Cube", pCube, cubeMaterial);
    debugCube->Scale() = {5, 5, 5};

    std::uniform_real_distribution<float> positionDist(-50.0f, 50.0);
    std::uniform_real_distribution<float> rotationDist(-20.0f, 20.0);
    std::uniform_real_distribution<float> scaleDist(0.1f, 1.5f);

    int numCubes = 1;

    for (int i = 0; i < numCubes; i++)
    {
        auto model = std::make_shared<Model>();
        model->Init(std::string("Cube ") + std::to_string(i), pCube, m_materials[matDist(rng)]);

        model->Position() = {
            positionDist(rng),
            positionDist(rng) * 0.5f + 25.0f,
            positionDist(rng),
        };

        model->Rotation() = {
            rotationDist(rng),
            rotationDist(rng),
            rotationDist(rng)
        };

        model->Scale() = {
            scaleDist(rng),
            scaleDist(rng),
            scaleDist(rng)
        };
        m_models.push_back(model);
    }
}