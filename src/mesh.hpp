//
// @author freemedude
// @date 2020-07-19
// @brief
//
#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "gpu_buffer.hpp"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
};

typedef u32 Index;

class Mesh
{
private:
    GpuBuffer m_vBuffer;
    GpuBuffer m_iBuffer;
public:
    u32 m_id;
    Mesh() = default;

    ~Mesh();

    void Init(std::vector<Vertex> &verts, std::vector<Index> &indices);

    void Bind();

    u64 Count();

    static std::shared_ptr<Mesh> make_quad()
    {
        std::vector<Vertex> verts = {
            {{-0.5, -0.5, 0}, {0, 0, 1}, {0, 0}},
            {{0.5,  -0.5, 0}, {0, 0, 1}, {1, 0}},
            {{0.5,  0.5,  0}, {0, 0, 1}, {1, 1}},
            {{-0.5, 0.5,  0}, {0, 0, 1}, {0, 1}},
        };

        std::vector<Index> indices = {
            0, 1, 2, 2, 3, 0
        };

        std::shared_ptr<Mesh> pMesh = std::make_shared<Mesh>();
        pMesh->Init(verts, indices);
        return pMesh;
    }

    static std::shared_ptr<Mesh> make_cube()
    {
        /*
         * FRONT
         *    6--------7
         *   /|       /|
         *  / |      / |
         * 3--------2  |
         * |  5-----|--4
         * | /      | /
         * |/       |/
         * 0--------1
         * BACK
         */
        glm::vec3 cornerPositions[]{
            {-0.5, -0.5, 0.5},
            {0.5,  -0.5, 0.5},
            {0.5,  0.5,  0.5},
            {-0.5, 0.5,  0.5},

            {0.5,  -0.5, -0.5},
            {-0.5, -0.5, -0.5},
            {-0.5, 0.5,  -0.5},
            {0.5,  0.5,  -0.5},
        };

        // Normals are used as color for now
        glm::vec3 normals[]{
            {0,  0,  1},
            {1,  0,  0},
            {0,  0,  -1},
            {-1, 0,  0},
            {0,  1,  0},
            {0,  -1, 0},
        };

        glm::vec2 uvs[]{
            {0,  0},
            {1,  0},
            {1,  1},
            {0, 1}
        };

        int positionOrder[]{
            0, 1, 2, 3,
            1, 4, 7, 2,
            4, 5, 6, 7,
            5, 0, 3, 6,
            3, 2, 7, 6,
            1, 0, 5, 4};

        std::vector<Vertex> vertices(24);
        for (int i = 0; i < vertices.size(); i++)
        {
            int cornerIndex = positionOrder[i];

            vertices[i] = {cornerPositions[cornerIndex], normals[i / 4], uvs[i % 4]};
        }

        // Look over indices and add face offset
        std::vector<Index> indices(36);

        for (int i = 0; i < indices.size(); i += 6)
        {
            int face = i / 6;
            int base = face * 4;

            indices[i + 0] = base + 0;
            indices[i + 1] = base + 1;
            indices[i + 2] = base + 2;
            indices[i + 3] = base + 2;
            indices[i + 4] = base + 3;
            indices[i + 5] = base + 0;
        }

        auto pMesh = std::make_shared<Mesh>();
        pMesh->Init(vertices, indices);
        return pMesh;
    }
};