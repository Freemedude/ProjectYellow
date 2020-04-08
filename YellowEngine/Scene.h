// Scene.h

#pragma once
#include <vector>

#include "Rendering.h"


namespace Yellow
{
class Scene
{
private:
	std::vector<Yellow::RenderObject> renderObjects;
public:
	std::vector<RenderObject>& RenderObjects();

	Scene();
	~Scene();
};
}
